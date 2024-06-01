/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:41:46 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/01 15:17:58 by bpisak-l         ###   ########.fr       */
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

void	print_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		printf("%s\n", arr[i]);
}
void	execute_command(char **argv, char **env)
{
	char	*cmd;

	cmd = get_cmd_path(argv[0], env);
	if (cmd)
		execve(cmd, argv, env);
	free(cmd);
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

int	main(int argc, char *argv[], char **env)
{
	char	**cmd_set;
	char	***cmds_set;
	int		i;
	int		fd[2];
	int		pid0;
	int		pid1;
	int		exit;

	if (argc != 2)
		return (0);
	cmd_set = ft_split(argv[1], '|');
	i = -1;
	cmds_set = ft_calloc(ft_arr_len(cmd_set) + 1, sizeof(char **));
	while (cmd_set[++i])
	{
		cmds_set[i] = ft_split(cmd_set[i], ' ');
		// print_arr(cmds_set[i]);
	}
	free_split_arr(cmd_set);
	i = -1;
	if (pipe(fd) < 0)
		set_error("pipe", 0);
	pid0 = fork();
	if (!pid0)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
			set_error("dup2", 0);
		close(fd[1]);
		execute_command(cmds_set[0], env);
	}
	pid1 = fork();
	if (!pid1)
	{
		close(fd[1]);
		if (dup2(fd[0], 0) == -1)
			set_error("dup2", 0);
		close(fd[0]);
		execute_command(cmds_set[1], env);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid0, &exit, 0);
	waitpid(pid1, &exit, 0);
	// while (cmds_set[++i])
	// {
	// 	execute_command(cmds_set[i], env);
	// }
	return (0);
}
