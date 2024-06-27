/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:58:49 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/27 13:37:19 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipes(char **cmd_set)
{
	int	fd[2];
	int	i;
	int	len;

	len = ft_arr_len(cmd_set);
	state()->pipes = ft_calloc(len + 2, sizeof(t_pipe));
	i = -1;
	while (cmd_set[++i])
	{
		if (i)
		{
			if (pipe(fd) < 0)
				set_error("pipe", 0, NULL);
			state()->pipes[i] = (t_pipe){.read = fd[0], .write = fd[1]};
		}
		else
			state()->pipes[i] = invalid_pipe();
	}
	state()->pipes[i] = invalid_pipe();
}

void	set_redirs(char **cmd_set)
{
	int	i;

	i = -1;
	while (cmd_set[++i])
	{
		state()->pipeline[i].argv = parse_redir(cmd_set[i], i);
		arr_remove_chars(state()->pipeline[i].argv, "\"\'");
	}
}
