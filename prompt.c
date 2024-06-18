/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/18 15:17:22 by bpisak-l         ###   ########.fr       */
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

char	***parse_line(char *line)
{
	char	**cmd_set;
	char	***cmds_set;
	int		i;

	if (!line || !*line)
		return (0);
	cmd_set = ft_split2(line, "|", "\"\'");
	if (!cmd_set)
		return (NULL);
	i = -1;
	cmds_set = ft_calloc(ft_arr_len(cmd_set) + 1, sizeof(char **));
	arr_expand_variables(cmd_set);
	while (cmd_set[++i])
	{
		cmds_set[i] = ft_split2(cmd_set[i], " \t", "\"\'");
		arr_remove_chars(cmds_set[i], "\"\'");
	}
	free_split_arr(cmd_set);
	return (cmds_set);
}

// ctrl-d exits minishell
int	main(int argc, char const *argv[], char **env)
{
	char	*line;
	char	***cmds_set;

	(void)argc;
	(void)argv;
	init_state(env);
	while (1)
	{
		line = readline("minishell$ ");
		if (line)
		{
			if (is_valid_syntax(line))
			{
				cmds_set = parse_line(line);
				execute_commands(cmds_set, NULL);
				printf("exitcode: %d\n", get_state()->exit_code);
				free_2d_split_arr(cmds_set);
			}
			add_history(line);
		}
		else
			free_and_exit();
		free(line);
	}
	return (0);
}
