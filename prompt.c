/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/26 11:48:21 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	ft_printf(1, "minishell: ");
}

void	reset_prompt(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("^C", 1);
	rl_redisplay();
	rl_replace_line("", 1);
	rl_redisplay();
}

// TODO:
void	init_signals(void)
{
	signal(SIGINT, reset_prompt);
}

// ctrl-d exits minishell
int	main(int argc, char const *argv[], char **env)
{
	char	*line;
	char	**cmd_set;
	int		syntax_correct;

	init_state(argc, argv, env);
	while (!state()->should_stop)
	{
		line = readline("minishell$ ");
		if (line)
		{
			if (*line)
			{
				syntax_correct = syntax_check(line);
				if (syntax_correct)
				{
					cmd_set = str_split(line, "|", "\"\'");
					arr_expand_variables(cmd_set);
					parse_line(cmd_set);
					free_split_arr(cmd_set);
					if (state()->pipeline && state()->pipeline[0].argv)
						execute_commands(state()->pipeline);
				}
				add_history(line);
			}
		}
		else
			free_and_exit();
		free(line);
		reset_state();
	}
	free_and_exit();
	return (0);
}
