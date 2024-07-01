/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/01 12:02:12 by bpisak-l         ###   ########.fr       */
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
	char	*temp_str;
	char	*temp_str2;
	int		i;
	int		j;

	cmd_set = str_split(line, "|", "\"\'");
	temp = cmd_set;
	state()->pipeline = ft_calloc(ft_arr_len(cmd_set) + 1, sizeof(t_stage));
	cmd_set = handle_heredocs(temp);
	free(temp);
	set_pipes(cmd_set);
	i = -1;
	while (cmd_set[++i])
	{
		temp_str = cmd_set[i];
		cmd_set[i] = handle_redirs(temp_str, i);
		free(temp_str);
	}
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
