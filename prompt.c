/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/21 18:44:22 by bpisak-l         ###   ########.fr       */
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
	int		fd[2];
	int		len;

	if (!line || !*line)
		return ;
	cmd_set = str_split(line, "|", "\"\'");
	len = ft_arr_len(cmd_set);
	// TODO:ERROR?
	if (!cmd_set)
		return ;
	i = -1;
	state()->pipeline = ft_calloc(len + 1, sizeof(t_stage));
	state()->pipes = ft_calloc(len + 2, sizeof(t_pipe));
	arr_expand_variables(cmd_set);
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
		state()->pipeline[i].argv = parse_redir(cmd_set[i], i);
		arr_remove_chars(state()->pipeline[i].argv, "\"\'");
	}
	state()->pipes[i] = invalid_pipe();
	free_split_arr(cmd_set);
}

// ctrl-d exits minishell
int	main(int argc, char const *argv[], char **env)
{
	char	*line;

	init_state(argc, argv, env);
	while (!state()->should_stop)
	{
		line = readline("minishell$ ");
		if (line)
		{
			syntax_check(line);
			if (state()->syntax_valid)
			{
				parse_line(line);
				execute_commands(state()->pipeline);
			}
			add_history(line);
		}
		else
			free_and_exit();
		free(line);
		reset_state();
	}
	free_and_exit();
	return (0);
}
