/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:21:34 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/20 12:09:38 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			buff[12];
	int				i;
	int				is_negative;
	unsigned int	abs;

	i = 1;
	is_negative = 0;
	buff[11] = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		is_negative = 1;
		abs = -n;
	}
	else
		abs = n;
	while (abs > 0)
	{
		buff[11 - i++] = abs % 10 + '0';
		abs = abs / 10;
	}
	if (is_negative)
		buff[11 - i++] = '-';
	return (ft_strdup(&buff[12 - i]));
}
