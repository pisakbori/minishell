/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:57:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/07 15:57:43 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*ucp_src;
	unsigned char		*ucp_dst;

	ucp_src = src;
	ucp_dst = dst;
	if (dst != 0 || src != 0)
		while (n--)
			ft_memset(ucp_dst + n, *(ucp_src + n), 1);
	return (dst);
}
