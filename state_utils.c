/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:39:08 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/29 10:48:58 by bpisak-l         ###   ########.fr       */
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
	char	*path_copy;

	path_copy = m_ft_strdup(oldcwd);
	set_env_variable("OLDPWD", path_copy);
	free(state()->oldcwd);
	state()->oldcwd = path_copy;
}

void	set_cwd(char *cwd)
{
	char	*path_copy;

	path_copy = m_ft_strdup(cwd);
	set_oldpwd(state()->cwd);
	free(state()->cwd);
	state()->cwd = path_copy;
	set_env_variable("PWD", path_copy);
}
