/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:38:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/18 15:31:59 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	jump_sign(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
	{
		*str = *str + 1;
		sign = -1;
	}
	else if (**str == '+')
		*str = *str + 1;
	return (sign);
}

char	ft_a_to_uchar(char *str)
{
	unsigned long long	res;
	int					i;
	int					sign;

	res = 0;
	i = 0;
	if (str_equal(str, "-9223372036854775808"))
		return (0);
	sign = jump_sign(&str);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (i >= 19 || res > 9223372036854775807)
		return (-1);
	res = sign * res;
	return ((unsigned char)res);
}

void	on_exit_b(t_exec e)
{
	int	code;

	if (e.argc == 1)
		state()->should_stop = 1;
	else if (e.argc > 2)
	{
		ft_printf(2, "exit: too many arguments\n");
		set_exit_code(1);
		return ;
	}
	else
	{
		code = ft_a_to_uchar(e.argv[1]);
		if (code == -1)
		{
			ft_printf(2, "exit: %s: numeric argument required\n", e.argv[1]);
			set_exit_code(2);
		}
		else
			set_exit_code(code);
	}
	state()->should_stop = 1;
}
