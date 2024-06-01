/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:41:46 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/01 12:45:51 by bpisak-l         ###   ########.fr       */
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

int	main(int argc, char *argv[], char **env)
{
	char	**cmd_set;
	char	***cmds_set;
	int		i;

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
	while (cmds_set[++i])
	{
		execute_command(cmds_set[i], env);
	}
	return (0);
}
