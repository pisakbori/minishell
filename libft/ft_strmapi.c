/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:26:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/11 14:43:17 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	size_t	i;

	i = 0;
	res = ft_strdup(s);
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = f(i, res[i]);
		i++;
	}
	return (res);
}
