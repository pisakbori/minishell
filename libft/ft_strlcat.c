/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:31:41 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/09 16:59:08 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// siz is the full size of dst, containting the NUL at the end
// At most siz-1 characters will be copied.
// Always NUL terminates (unless strlen(dst) > siz).
// Returns strlen(src) + MIN(siz, strlen(initial dst))

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst >= dstsize)
		return (len_src + dstsize);
	i = 0;
	while (i < dstsize - len_dst - 1 && src[i] != 0)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = 0;
	return (len_dst + len_src);
}
