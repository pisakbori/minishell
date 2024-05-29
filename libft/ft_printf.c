/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:56:28 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/04/08 17:22:54 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_arg(const char conversion, va_list arg, int *counter)
{
	char	*dec;
	char	*lc_hex_base;
	char	*uc_hex_base;

	dec = "0123456789";
	lc_hex_base = "0123456789abcdef";
	uc_hex_base = "0123456789ABCDEF";
	if (conversion == '%')
		return (ft_cprint('%', counter));
	if (conversion == 'c')
		return (ft_cprint(va_arg(arg, int), counter));
	if (conversion == 's')
		return (ft_sprint(va_arg(arg, char *), counter));
	if (conversion == 'd' || conversion == 'i')
		return (ft_dxprint(va_arg(arg, int), counter, 10, dec));
	if (conversion == 'u')
		return (ft_uprint(va_arg(arg, unsigned long), counter, 10, dec));
	if (conversion == 'p')
		return (ft_pprint(va_arg(arg, unsigned long), counter));
	if (conversion == 'x')
		return (ft_dxprint(va_arg(arg, int), counter, 16, lc_hex_base));
	if (conversion == 'X')
		return (ft_dxprint(va_arg(arg, int), counter, 16, uc_hex_base));
	return (0);
}

int	ft_printf(const char *format_str, ...)
{
	char		*iter;
	va_list		arg;
	int			counter;

	counter = 0;
	va_start(arg, format_str);
	iter = (char *)format_str;
	while (*iter)
	{
		if (*iter == '%')
		{
			iter++;
			if (ft_print_arg(*iter, arg, &counter) == -1)
				return (-1);
		}
		else
		{
			if (ft_cprint(*iter, &counter) == -1)
				return (-1);
		}
		iter++;
	}
	return (counter);
}
