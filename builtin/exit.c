/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:38:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/23 17:11:11 by bpisak-l         ###   ########.fr       */
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

unsigned char	ft_a_to_uchar(char *str)
{
	unsigned long long	res;
	int					i;
	int					sign;

	res = 0;
	i = 0;
	if (!ft_strlen(str))
	{
		ft_printf(2, "exit: %s: numeric argument required\n", str);
		return (2);
	}
	if (str_equal(str, "-9223372036854775808"))
		return (0);
	sign = jump_sign(&str);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_printf(2, "exit: %s: numeric argument required\n", str);
			return (2);
		}
		res = res * 10 - '0' + str[i];
		i++;
	}
	if (i >= 19 && res < 776627963145224191)
	{
		ft_printf(2, "exit: %s: numeric argument required\n", str);
		return (2);
	}
	if (sign > 0)
		return ((unsigned char)res);
	else
		return (256 - (unsigned char)res);
}

void	on_exit_b(t_exec e)
{
	unsigned char	code;

	if (e.argc == 1)
		state()->should_stop = 1;
	else
	{
		code = ft_a_to_uchar(e.argv[1]);
		set_exit_code(code);
		state()->should_stop = 1;
		return ;
	}
	if (e.argc > 2)
	{
		ft_printf(2, "exit: too many arguments\n");
		set_exit_code(1);
		return ;
	}
	state()->should_stop = 1;
}
