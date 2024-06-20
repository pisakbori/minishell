/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:38:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/20 12:05:50 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// TODO:
int	is_valid_int(char *str)
{
	int	i;

	i = 0;
	if (str_has("-+", str[i]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_with_code(t_exec e)
{
	int	exit_code;

	exit_code = ft_atoi(e.argv[1]);
	set_exit_code(exit_code);
	if (exit_code)
		ft_printf(1, "exit\n");
	else
		ft_printf(1, "exit\n");
	free_and_exit();
}

void	on_exit_b(t_exec e)
{
	if (e.argc == 1)
	{
		ft_printf(1, "exit\n");
		free_and_exit();
	}
	else if (e.argc > 2)
	{
		ft_printf(2, "exit: too many arguments\n");
		set_exit_code(1);
	}
	else if (!is_valid_int(e.argv[1]))
	{
		ft_printf(2, "exit: %s: numeric argument required\n", e.argv[1]);
		set_exit_code(2);
	}
	else
		exit_with_code(e);
}
