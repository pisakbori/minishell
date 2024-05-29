/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_reverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:34:53 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/04/13 15:56:13 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_reverse(char *str, size_t reversed_len, int *counter)
{
	if (!reversed_len)
		*counter = -1;
	while (reversed_len > 0)
	{
		ft_cprint(str[reversed_len - 1], counter);
		if (*counter == -1)
			return (-1);
		reversed_len--;
	}
	return (*counter);
}
