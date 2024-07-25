/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:25:04 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/24 15:58:33 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	on_env(t_exec e)
{
	char	**env;

	if (e.argc > 1)
	{
		ft_printf(2, "env: %s: no options or arguments allowed\n", e.argv[1]);
		set_exit_code(127);
		return ;
	}
	set_env_variable("_", "/usr/bin/env");
	env = state()->env;
	print_array(env);
	set_exit_code(0);
}
