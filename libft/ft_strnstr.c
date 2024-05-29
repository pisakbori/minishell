/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:52:38 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/11 13:06:24 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_needle;

	i = 0;
	len_needle = ft_strlen(needle);
	if (!len_needle)
		return ((char *)haystack);
	while (i < len && haystack[i] && i + len_needle <= len)
	{
		if (!ft_strncmp(haystack + i, needle, len_needle))
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
