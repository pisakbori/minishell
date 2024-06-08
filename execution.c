/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:22:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/08 15:05:16 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_code(int ext)
{
	if (WIFSIGNALED(ext))
		return (128 + WTERMSIG(ext));
	else if (WIFEXITED(ext))
		return (WEXITSTATUS(ext));
	else
		return (ext);
}

int	execute_command(char **argv, char **env)
{
	char	*cmd;
	int		res;

	cmd = get_cmd_path(argv[0], env);
	if (cmd)
		res = execve(cmd, argv, env);
	else
	{
		ft_printf(2, "%s: command not found\n", argv[0]);
		res = 127;
	}
	free(cmd); //TODO: when?????
	return (res);
}

void	execute_cmd(char **argv, t_pipe *left_p, t_pipe *right_p, char **env)
{
	int	res;

	if (right_p)
	{
		close(right_p->read);
		if (dup2(right_p->write, 1) == -1)
			set_error("dup2 right", 0);
		close(right_p->write);
	}
	if (left_p)
	{
		close(left_p->write);
		if (dup2(left_p->read, 0) == -1)
			set_error("dup2 left", 0);
		close(left_p->read);
	}
	res = execute_command(argv, env);
	exit(res);
}
void	close_pipe(t_pipe *p)
{
	if (p)
	{
		close(p->read);
		close(p->write);
	}
}
void	execute_rightmost(int *exit, char **cmd, t_pipe *left_p, char **env)
{
	t_pipe	right_p;
	int		fd[2];
	int		pid1;

	if (pipe(fd) < 0)
		set_error("pipe", 0);
	right_p = (t_pipe){.read = fd[0], .write = fd[1]};
	pid1 = fork();
	right_p.read = dup(0);
	right_p.write = dup(1);
	if (!pid1)
		execute_cmd(cmd, left_p, &right_p, env);
	close_pipe(left_p);
	close_pipe(&right_p);
	waitpid(pid1, exit, 0);
	*exit = error_code(*exit);
}
void	execute_with_pipe(char ***cmds_set, char **env, t_pipe *left_p,
		int *exit)
{
	int		temp;
	t_pipe	right_p;
	int		fd[2];
	int		pid1;

	if (pipe(fd) < 0)
		set_error("pipe", 0);
	right_p = (t_pipe){.read = fd[0], .write = fd[1]};
	pid1 = fork();
	if (!pid1)
		execute_cmd(*cmds_set, left_p, &right_p, env);
	close_pipe(left_p);
	execute_commands(cmds_set + 2, env, &right_p, exit);
	close_pipe(&right_p);
	waitpid(pid1, &temp, 0);
}

// TODO: handle semicolon
void	execute_commands(char ***cmds_set, char **env, t_pipe *left_p,
		int *exit)
{
	if (ft_arr_3d_len(cmds_set) > 2)
	{
		if (str_equal(cmds_set[1][0], "|"))
			execute_with_pipe(cmds_set, env, left_p, exit);
	}
	else
		execute_rightmost(exit, cmds_set[0], left_p, env);
}
