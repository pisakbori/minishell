/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:20:44 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/04/29 17:23:44 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strjoin_dupe(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src)
		return ;
	if (dstsize > 1)
	{
		while (i < dstsize - 1 && *(src + i))
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = 0;
	}
}

char	*ft_strchr_dupe(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == (char) c)
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*collect_garbage(char **result_str, char **buff)
{
	if (*result_str)
	{
		free(*result_str);
		*result_str = 0;
	}
	free(*buff);
	return (NULL);
}
