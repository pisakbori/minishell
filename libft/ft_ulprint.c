/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:01:40 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/04/08 17:24:49 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ulprint(unsigned long n, int *counter, int base, char *digits)
{
	char	res[21];
	int		reversed_len;

	if (n == 0)
	{
		ft_cprint('0', counter);
		return (1);
	}
	reversed_len = 0;
	while (n > 0)
	{
		res[reversed_len] = digits[n % base];
		reversed_len++;
		n = n / base;
	}
	return (print_reverse(res, reversed_len, counter));
}

int	ft_uprint(unsigned long n, int *counter, int base, char *digits)
{
	n = (unsigned int) n;
	return (ft_ulprint(n, counter, base, digits));
}

int	ft_pprint(unsigned long n, int *counter)
{
	ft_sprint("0x", counter);
	if (*counter != -1)
		ft_ulprint(n, counter, 16, "0123456789abcdef");
	return (*counter);
}
