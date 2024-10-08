/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:38:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/29 17:15:27 by bpisak-l         ###   ########.fr       */
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

int	on_non_numeric_arg(char *str)
{
	print_err_prompt();
	ft_printf(2, "exit: %s: numeric argument required\n", str);
	set_exit_code(2);
	return (-1);
}

int	ft_a_to_uchar(char *str)
{
	unsigned long long	res;
	int					i;
	int					sign;

	res = 0;
	i = 0;
	if (!ft_strlen(str))
		return (on_non_numeric_arg(str));
	if (str_equal(str, "-9223372036854775808"))
		return (0);
	sign = jump_sign(&str);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (on_non_numeric_arg(str));
		res = res * 10 - '0' + str[i];
		i++;
	}
	if (i > 19 || (res > 9223372036854775807))
		return (on_non_numeric_arg(str));
	if (sign > 0)
		return ((unsigned char)res);
	else
		return (256 - (unsigned char)res);
}

void	on_exit_b(t_exec e)
{
	int	code;

	if (e.argc == 1)
	{
		state()->should_stop = 1;
		return ;
	}
	code = ft_a_to_uchar(e.argv[1]);
	if (code == -1)
		state()->should_stop = 1;
	else if (e.argc > 2)
		set_mini_error("exit", 1, "too many arguments");
	else
	{
		set_exit_code(code);
		state()->should_stop = 1;
	}
}
