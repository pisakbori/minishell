/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:41:46 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/08 14:57:39 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	execute_commands(cmds_set, env, NULL, &res);
	free_2d_split_arr(cmds_set);
	printf("$? = %d\n", res);
	return (0);
}
