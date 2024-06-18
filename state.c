/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:47:59 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/18 15:30:20 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	**get_state_ptr(void)
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

void	init_state(char **env)
{
	t_state	*state;

	state = ft_calloc(1, sizeof(t_state));
	state->exit_code = 0;
	state->env = clone_str_arr(env);
	set_state(state);
}
