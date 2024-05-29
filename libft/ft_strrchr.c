/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:31:22 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/08 16:51:35 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	char	*match;

	match = NULL;
	last = (char *)s;
	while (*last)
	{
		if (*last == (char)c)
			match = last;
		last++;
	}
	if (!(char)c)
		return (last);
	else
		return (match);
}
