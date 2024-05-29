/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:11:24 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/11 14:23:22 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*res;

	len = ft_strlen(s1);
	res = (char *)malloc((len + 1) * sizeof(char ));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len + 1);
	return (res);
}
