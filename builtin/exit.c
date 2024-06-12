/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:38:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/12 20:25:47 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// TODO:
int	is_valid_int(char *str)
{
	(void)str;
	return (1);
}

void	on_exit_b(t_exec e)
{
	int	exit_code;

	// TODO: exit with last exitcode;
	if (e.argc == 1)
	{
		ft_printf(1, "exit\n");
		exit(get_state()->exit_code);
	}
	else if (e.argc > 2)
	{
		ft_printf(2, "exit: too many arguments\n");
		set_exit_code(1);
	}
	else if (!is_valid_int(e.argv[1]))
	{
		ft_printf(2, "exit: %s: numeric argument required\n", e.argv[0]);
		set_exit_code(2);
	}
	else
	{
		exit_code = ft_atoi(e.argv[1]);
		set_exit_code(exit_code);
		if (exit_code)
			ft_printf(2, "exit\n");
		else
			ft_printf(1, "exit\n");
	}
	// free_exit(0);
}
