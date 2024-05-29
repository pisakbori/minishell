/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:29:19 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/04/15 13:50:03 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (len1 + len2) + 1);
	if (res)
	{
		ft_strlcpy(res, s1, len1 + 1);
		ft_strlcpy(res + len1, s2, len2 + 1);
	}
	return (res);
}
