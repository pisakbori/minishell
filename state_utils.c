/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:39:08 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/21 11:37:56 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_arg(char *arg)
{
	t_state	*s;

	s = state();
	free(s->last_arg);
	s->last_arg = ft_strdup(arg);
}

void	set_exit_code(int exit_code)
{
	t_state	*s;

	s = state();
	s->exit_code = exit_code;
}

void	set_oldpwd(char *oldcwd)
{
	t_state	*s;

	s = state();
	set_env_variable("OLDPWD", oldcwd);
	free(s->oldcwd);
	s->oldcwd = ft_strdup(oldcwd);
}

void	set_cwd(char *cwd)
{
	t_state	*s;

	s = state();
	set_oldpwd(s->cwd);
	free(s->cwd);
	s->cwd = ft_strdup(cwd);
	set_env_variable("PWD", cwd);
}
