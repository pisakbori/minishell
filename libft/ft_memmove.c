/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:27:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/08 11:27:03 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*ucp_src;
	unsigned char		*ucp_dst;
	size_t				i;

	ucp_src = src;
	ucp_dst = dst;
	i = 0;
	if (dst == 0 && src == 0)
		return (dst);
	if (dst < src)
	{
		while (i < len)
		{
			ft_memcpy(ucp_dst + i, ucp_src + i, 1);
			i++;
		}
	}
	else
		while (len-- > 0)
			ft_memcpy(ucp_dst + len, ucp_src + len, 1);
	return (dst);
}
