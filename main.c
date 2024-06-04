/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:41:46 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/04 11:17:51 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split_arr(char **res)
{
	int	i;

	i = ft_arr_len(res) + 1;
	while (--i >= 0)
		free(*(res + i));
	free(res);
}

void	free_2d_split_arr(char ***res)
{
	int	i;

	i = -1;
	while (res[++i])
		free_split_arr(res[i]);
	free(res);
}

void	print_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		printf("%s\n", arr[i]);
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

int	error_code(int ext)
{
	if (WIFSIGNALED(ext))
		return (128 + WTERMSIG(ext));
	else if (WIFEXITED(ext))
		return (WEXITSTATUS(ext));
	else
		return (ext);
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

int	execute_commands(char ***cmds_set, char **env, t_pipe *left_p)
{
	t_pipe	right_p;
	int		fd[2];
	int		pid1;
	int		exit;
	int		temp;

	if (cmds_set[0] && !cmds_set[1])
	{
		if (pipe(fd) < 0)
			set_error("pipe", 0);
		right_p = (t_pipe){.read = fd[0], .write = fd[1]};
		pid1 = fork();
		right_p.read = dup(0);
		right_p.write = dup(1);
		if (!pid1)
			execute_cmd(cmds_set[0], left_p, &right_p, env);
		if (left_p)
		{
			close(left_p->read);
			close(left_p->write);
		}
		close(right_p.read);
		close(right_p.write);
		waitpid(pid1, &exit, 0);
	}
	else if (cmds_set[2])
	{
		if (str_equal(cmds_set[1][0], "|"))
		{
			if (pipe(fd) < 0)
				set_error("pipe", 0);
			right_p = (t_pipe){.read = fd[0], .write = fd[1]};
			pid1 = fork();
			if (!pid1)
				execute_cmd(*cmds_set, left_p, &right_p, env);
			if (left_p)
			{
				close(left_p->read);
				close(left_p->write);
			}
			execute_commands(cmds_set + 2, env, &right_p);
			close(right_p.read);
			close(right_p.write);
			waitpid(pid1, &temp, 0);
		}
	}
	return (error_code(exit));
}

int	main(int argc, char *argv[], char **env)
{
	char	**cmd_set;
	char	***cmds_set;
	int		i;
	int		res;

	if (argc != 2)
		return (0);
	cmd_set = ft_split_and_keep(argv[1], "|;");
	i = -1;
	cmds_set = ft_calloc(ft_arr_len(cmd_set) + 1, sizeof(char **));
	while (cmd_set[++i])
	{
		cmds_set[i] = ft_split(cmd_set[i], ' ');
		// print_arr(cmds_set[i]);
	}
	free_split_arr(cmd_set);
	res = execute_commands(cmds_set, env, NULL);
	free_2d_split_arr(cmds_set);
	printf("$? = %d\n", res);
	return (0);
}
