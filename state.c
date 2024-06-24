/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:47:59 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/24 14:58:53 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	**get_state_ptr(void)
{
	static t_state	*state;

	return (&state);
}

t_state	*state(void)
{
	return (*get_state_ptr());
}

void	set_state(t_state *val)
{
	t_state	**state;

	state = get_state_ptr();
	*state = val;
}

void	init_state(int argc, char const *argv[], char **env)
{
	t_state	*state;

	(void)argc;
	(void)argv;
	state = ft_calloc(1, sizeof(t_state));
	state->exit_code = 0;
	state->env = clone_str_arr(env);
	state->cwd = getcwd(NULL, 0);
	state->syntax_valid = 1;
	state->backup_stdin = dup(STDIN_FILENO);
	state->backup_stdout = dup(STDOUT_FILENO);
	state->should_stop = 0;
	state->pipeline = NULL;
	set_state(state);
}
void	reset_stdio(void)
{
	dup2(state()->backup_stdin, STDIN_FILENO);
	dup2(state()->backup_stdout, STDOUT_FILENO);
}

void	reset_state(void)
{
	reset_stdio();
	state()->syntax_valid = 1;
	free_pipeline();
}
