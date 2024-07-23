/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/23 17:52:39 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err_prompt(void)
{
	ft_printf(2, "minishell: ");
}

void	execute_line(char *line)
{
	char	**cmd_set;
	char	**temp;

	cmd_set = str_split(line, "|", "\"\'");
	temp = cmd_set;
	state()->pipeline = ft_calloc(ft_arr_len(cmd_set) + 1, sizeof(t_stage));
	cmd_set = handle_heredocs(temp);
	free_split_arr(temp);
	set_pipes(cmd_set);
	set_and_remove_redirs(cmd_set);
	set_pipeline_argvs(cmd_set);
	free_split_arr(cmd_set);
	if (state()->pipeline && state()->pipeline[0].argv)
		execute_commands(state()->pipeline);
}

// ctrl-d exits minishell
int	main(int argc, char const *argv[], char **env)
{
	char	*line;

	init_signals();
	init_state(argc, argv, env);
	while (!state()->should_stop)
	{
		if (isatty(fileno(stdin)))
			line = readline("minishell$ ");
		else
		{
			line = get_next_line(fileno(stdin));
			line = ft_strtrim(line, "\n");
		}
		if (line && *line)
		{
			let_signals_through();
			if (is_valid_syntax(line))
				execute_line(line);
			add_history(line);
		}
		else if (!line)
			free_and_exit();
		free(line);
		reset_state();
	}
	free_and_exit();
	return (0);
}
