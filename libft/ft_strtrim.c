/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:48:34 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/08 18:14:08 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*current;

	current = (char *)s1;
	end = 0;
	start = 0;
	while (*current && ft_strchr(set, *current))
		current++;
	start = current - s1;
	while (*current)
	{
		if (!ft_strchr(set, *current))
			end = current - s1;
		current++;
	}
	return (ft_substr(s1, start, end - start + 1));
}
