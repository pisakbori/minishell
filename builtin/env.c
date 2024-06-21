/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:25:04 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/21 11:32:37 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	on_env(t_exec e)
{
	char	**env;

	(void)e;
	set_env_variable("_", "/usr/bin/env");
	env = state()->env;
	print_array(env);
	set_exit_code(0);
}
