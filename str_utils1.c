/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:31:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/19 14:11:19 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	str_contains(char *str, char c)
{
	return (ft_strchr(str, c) != NULL);
}

int	str_equal(char *str1, char *str2)
{
	int	len1;
	int	len2;

	if (!str1 && !str2)
		return (1);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 != len2)
		return (0);
	return (!ft_strncmp(str1, str2, len1));
}

char	*ft_str_append(char *str1, char *str2)
{
	char	*res;

	res = ft_strjoin(str1, str2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	// TODO:exit on error;
	return (res);
}

char	*next_nonalpha(char *s)
{
	while (s && *s)
	{
		if (!ft_isalnum(*s) && *s != '_')
			break ;
		s++;
	}
	return (s);
}

int	starts_with(char *str, char *start)
{
	return (!ft_strncmp(str, start, ft_strlen(start)));
}
