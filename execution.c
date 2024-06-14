/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:22:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/14 10:55:03 by bpisak-l         ###   ########.fr       */
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
int	is_builtin(char *cmd)
{
	int	is_bltn;

	is_bltn = 0;
	is_bltn = str_equal(cmd, "exit");
	is_bltn = is_bltn || str_equal(cmd, "export");
	is_bltn = is_bltn || str_equal(cmd, "unset");
	is_bltn = is_bltn || str_equal(cmd, "env");
	return (is_bltn);
}

int	execute_command(char **argv)
{
	char	*cmd;
	int		res;
	char	**env;

	env = get_state()->env;
	if (!argv)
	{
		ft_printf(2, "Syntax error");
		return (2);
	}
	cmd = get_cmd_path(argv[0]);
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

void	execute_cmd(char **argv, t_pipe *left_p, t_pipe *right_p)
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
	res = execute_command(argv);
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
void	execute_rightmost(char **cmd, t_pipe *left_p)
{
	t_pipe	right_p;
	int		fd[2];
	int		pid1;
	int		exit;

	if (is_builtin(cmd[0]))
	{
		exec_builtin(cmd);
		return ;
	}
	exit = get_state()->exit_code;
	if (pipe(fd) < 0)
		set_error("pipe", 0);
	right_p = (t_pipe){.read = fd[0], .write = fd[1]};
	pid1 = fork();
	right_p.read = dup(0);
	right_p.write = dup(1);
	if (!pid1)
		execute_cmd(cmd, left_p, &right_p);
	close_pipe(left_p);
	close_pipe(&right_p);
	waitpid(pid1, &exit, 0);
	set_exit_code(error_code(exit));
}
void	execute_with_pipe(char ***cmds_set, t_pipe *left_p)
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
		execute_cmd(*cmds_set, left_p, &right_p);
	close_pipe(left_p);
	execute_commands(cmds_set + 1, &right_p);
	close_pipe(&right_p);
	waitpid(pid1, &temp, 0);
}

void	execute_commands(char ***cmds_set, t_pipe *left_p)
{
	if (!cmds_set)
		return ;
	if (ft_arr_3d_len(cmds_set) > 1)
	{
		execute_with_pipe(cmds_set, left_p);
	}
	else
		execute_rightmost(cmds_set[0], left_p);
}
