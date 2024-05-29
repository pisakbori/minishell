/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:52:08 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/08 18:14:12 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*first;

	first = (char *)s;
	while (*first)
	{
		if (*first == (char)c)
			return (first);
		first++;
	}
	if (!(char)c)
		return (first);
	else
		return (0);
}
