/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:39:08 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/18 15:16:53 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_arg(char *arg)
{
	t_state	*state;

	state = get_state();
	free(state->last_arg);
	state->last_arg = ft_strdup(arg);
}

void	set_exit_code(int exit_code)
{
	t_state	*state;

	state = get_state();
	state->exit_code = exit_code;
}

void	set_oldpwd(char *oldcwd)
{
	t_state	*state;

	state = get_state();
	set_env_variable("OLDPWD", oldcwd);
	free(state->oldcwd);
	state->oldcwd = ft_strdup(oldcwd);
}

void	set_cwd(char *cwd)
{
	t_state	*state;

	state = get_state();
	set_oldpwd(state->cwd);
	free(state->cwd);
	state->cwd = ft_strdup(cwd);
	set_env_variable("PWD", cwd);
}