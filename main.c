/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/29 12:29:37 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_leftovers(char **cmd_set)
{
	int	i;

	i = -1;
	while (cmd_set[++i])
	{
		free(cmd_set[i]);
		free(state()->pipeline[i].redir.in);
	}
	free(cmd_set);
}

void	execute_line(char *line)
{
	char	**cmd_set;
	char	**temp;

	cmd_set = str_split(line, "|", "\"\'");
	temp = cmd_set;
	state()->pipeline = m_ft_calloc(ft_arr_len(cmd_set) + 1, sizeof(t_stage));
	cmd_set = handle_heredocs(temp);
	free_split_arr(temp);
	if (state()->heredocs_ok)
	{
		set_pipes(cmd_set);
		set_and_remove_redirs(cmd_set);
		set_pipeline_argvs(cmd_set);
		free_split_arr(cmd_set);
		if (state()->pipeline && state()->pipeline[0].argv)
			execute_commands(state()->pipeline);
	}
	else
		free_leftovers(cmd_set);
}

char	*read_debug(char *prompt)
{
	char	*temp;
	char	*hd_line;

	hd_line = NULL;
	if (isatty(fileno(stdin)))
		hd_line = readline(prompt);
	else
	{
		hd_line = get_next_line(fileno(stdin));
		temp = hd_line;
		hd_line = ft_strtrim(hd_line, "\n");
		free(temp);
	}
	return (hd_line);
}
// char	*read_debug(char *prompt)
// {
// 	char	*hd_line;

// 	hd_line = readline(prompt);
// 	return (hd_line);
// }

// ctrl-d exits minishell
int	main(int argc, char const *argv[], char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	init_state(env);
	while (!state()->should_stop)
	{
		reset_state();
		line = read_debug("minishell$ ");
		if (line && *line)
		{
			let_signals_through();
			if (is_valid_syntax(line))
				execute_line(line);
			add_history(line);
		}
		else if (!line)
			free_and_exit(0);
		free(line);
	}
	free_and_exit(0);
	return (0);
}
