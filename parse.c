/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:58:49 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/29 17:20:29 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_fail(void)
{
	ft_printf(2, "Pipe fail.");
	state()->exit_code = EPIPE;
	free_and_exit();
}

void	set_pipes(char **cmd_set)
{
	int		fd[2];
	int		i;
	int		len;
	t_pipe	p;

	len = ft_arr_len(cmd_set);
	state()->pipes = m_ft_calloc(len + 2, sizeof(t_pipe));
	i = -1;
	while (cmd_set[++i])
	{
		if (i)
		{
			if (pipe(fd) < 0)
				pipe_fail();
			p = (t_pipe){.read = fd[0], .write = fd[1]};
			state()->pipes[i] = p;
		}
		else
			state()->pipes[i] = invalid_pipe();
	}
	state()->pipes[i] = invalid_pipe();
}

void	set_and_remove_redirs(char **cmd_set)
{
	char	*temp_str;
	int		i;

	i = -1;
	while (cmd_set[++i])
	{
		temp_str = cmd_set[i];
		cmd_set[i] = handle_redirs(temp_str, i);
		free(temp_str);
	}
}

void	set_pipeline_argvs(char **cmd_set)
{
	int		i;
	int		j;
	char	*temp_str2;
	char	*temp_str;
	char	**temp;

	i = -1;
	while (cmd_set[++i])
	{
		temp_str = cmd_set[i];
		cmd_set[i] = expand_variables(cmd_set[i], "\'\"");
		free(temp_str);
		temp = str_split(cmd_set[i], " \t", "\"\'");
		j = -1;
		while (temp[++j])
		{
			temp_str2 = temp[j];
			temp[j] = remove_chars(temp[j], "\"\'");
			replace_special_chars(temp[j]);
			free(temp_str2);
		}
		state()->pipeline[i].argv = temp;
	}
}
