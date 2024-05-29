/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:08:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/11 13:18:13 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*res;
	size_t	i;
	size_t	total_size;

	i = 0;
	total_size = count * size;
	res = malloc(total_size);
	if (!res)
		return (NULL);
	while (i < total_size)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}
