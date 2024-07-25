/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:39:08 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 13:26:41 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_arg(char *arg)
{
	t_state	*s;

	s = state();
	free(s->last_arg);
	s->last_arg = m_ft_strdup(arg);
}

void	set_exit_code(int exit_code)
{
	t_state	*s;

	s = state();
	s->exit_code = exit_code;
}

void	set_oldpwd(char *oldcwd)
{
	set_env_variable("OLDPWD", oldcwd);
	free(state()->oldcwd);
	state()->oldcwd = m_ft_strdup(oldcwd);
}

void	set_cwd(char *cwd)
{
	set_oldpwd(state()->cwd);
	free(state()->cwd);
	state()->cwd = m_ft_strdup(cwd);
	set_env_variable("PWD", cwd);
}
