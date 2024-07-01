/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/01 12:27:41 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	ft_printf(1, "minishell: ");
}

void	execute_line(char *line)
{
	char	**cmd_set;
	char	**temp;

	cmd_set = str_split(line, "|", "\"\'");
	temp = cmd_set;
	state()->pipeline = ft_calloc(ft_arr_len(cmd_set) + 1, sizeof(t_stage));
	cmd_set = handle_heredocs(temp);
	free(temp);
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
		line = readline("minishell$ ");
		if (line && *line)
		{
			if (is_valid_syntax(line, 0))
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
