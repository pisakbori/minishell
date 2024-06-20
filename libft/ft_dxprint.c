/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dxprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:42:36 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/20 12:10:11 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dxprint(int n, int *counter, int base, char *digits)
{
	char			res[21];
	int				reversed_len;
	unsigned int	abs;

	if (n < 0 && base == 10)
	{
		ft_cprint('-', counter);
		abs = (unsigned int)-n;
		if (*counter == -1)
			return (-1);
	}
	else
		abs = (unsigned int)n;
	if (n == 0)
		return (ft_cprint('0', counter));
	reversed_len = 0;
	while (abs > 0)
	{
		res[reversed_len] = digits[abs % base];
		reversed_len++;
		abs = abs / base;
	}
	return (print_reverse(res, reversed_len, counter));
}
