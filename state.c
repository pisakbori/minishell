/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:47:59 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/14 13:47:25 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_state	**get_state_ptr(void)
{
	static t_state	*state;

	return (&state);
}

t_state	*get_state(void)
{
	return (*get_state_ptr());
}

void	set_state(t_state *val)
{
	t_state	**state;

	state = get_state_ptr();
	*state = val;
}

void	set_exit_code(int exit_code)
{
	t_state	*state;

	state = get_state();
	state->exit_code = exit_code;
}

void	set_env(char **env)
{
	t_state	*state;

	state = get_state();
	state->env = env;
}

void	set_last_arg(char *arg)
{
	t_state	*state;

	state = get_state();
	// free(state->last_arg);
	state->last_arg = ft_strdup(arg);
}
