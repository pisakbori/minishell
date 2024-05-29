/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:33:22 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/11 11:08:08 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	s_len;
	size_t	res_len;

	s_len = ft_strlen((const char *)s);
	res_len = s_len - start;
	if (s_len < start || !s)
		res_len = 0;
	else if (len < res_len)
		res_len = len;
	res = (char *) malloc(sizeof(char) * (res_len + 1));
	if (!res)
		return (NULL);
	if (res_len)
		ft_strlcpy(res, s + start, res_len + 1);
	else
		*res = 0;
	return (res);
}
