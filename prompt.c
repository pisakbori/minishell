/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/20 12:41:07 by bpisak-l         ###   ########.fr       */
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

void	parse_line(char *line)
{
	char	**cmd_set;
	int		i;

	if (!line || !*line)
		return ;
	cmd_set = str_split(line, "|", "\"\'");
	// TODO:ERROR?
	if (!cmd_set)
		return ;
	i = -1;
	// table_cmd_args = ft_calloc(ft_arr_len(cmd_set) + 1, sizeof(char **));
	get_state()->pipeline = ft_calloc(ft_arr_len(cmd_set) + 1, sizeof(t_stage));
	arr_expand_variables(cmd_set);
	while (cmd_set[++i])
	{
		get_state()->pipeline[i].argv = parse_redir(cmd_set[i], i);
		arr_remove_chars(get_state()->pipeline[i].argv, "\"\'");
	}
	free_split_arr(cmd_set);
	// return (table_cmd_args);
}

// ctrl-d exits minishell
int	main(int argc, char const *argv[], char **env)
{
	char	*line;

	// char	***table_cmd_args;
	(void)argc;
	(void)argv;
	init_state(env);
	while (1)
	{
		get_state()->syntax_valid = 1;
		line = readline("minishell$ ");
		if (line)
		{
			if (is_valid_syntax(line))
			{
				parse_line(line);
				execute_commands(get_state()->pipeline, NULL);
				// free_2d_split_arr(table_cmd_args);
			}
			add_history(line);
		}
		else
			free_and_exit();
		free(line);
	}
	return (0);
}
