/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:58:09 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/12 10:53:53 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_reverse_str(char *str, size_t reversed_len, int fd)
{
	while (reversed_len > 0)
	{
		ft_putchar_fd(str[reversed_len - 1], fd);
		reversed_len--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char			res[10];
	int				reversed_len;
	unsigned int	abs;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		abs = (unsigned int) -n;
	}
	else
		abs = (unsigned int) n;
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	reversed_len = 0;
	while (abs > 0)
	{
		res[reversed_len] = abs % 10 + '0';
		reversed_len++;
		abs = abs / 10;
	}
	print_reverse_str(res, reversed_len, fd);
}
