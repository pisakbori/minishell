/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/27 14:29:21 by bpisak-l         ###   ########.fr       */
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

void	execute_line(char *line)
{
	char	**cmd_set;
	char	**temp;

	cmd_set = str_split(line, "|", "\"\'");
	temp = cmd_set;
	state()->pipeline = ft_calloc(ft_arr_len(cmd_set) + 1, sizeof(t_stage));
	cmd_set = handle_heredocs(temp);
	free(temp);
	arr_expand_variables(cmd_set);
	set_pipes(cmd_set);
	set_redirs(cmd_set);
	free_split_arr(cmd_set);
	if (state()->pipeline && state()->pipeline[0].argv)
		execute_commands(state()->pipeline);
}

// ctrl-d exits minishell
int	main(int argc, char const *argv[], char **env)
{
	char	*line;

	init_state(argc, argv, env);
	while (!state()->should_stop)
	{
		line = readline("minishell$ ");
		if (line && *line)
		{
			if (syntax_check(line))
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
