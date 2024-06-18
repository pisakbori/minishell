/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:53:54 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/18 15:21:51 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ends_with_char(char *str, char c)
{
	return (str && *str && str[ft_strlen(str) - 1] == c);
}

void	ft_replace_chars(char *str, char *map, int c)
{
	int	i;

	i = -1;
	if (!str || !map)
		return ;
	if (ft_strlen(map) != ft_strlen(str))
		return ;
	while (map[++i])
	{
		if (map[i] == 'd')
			str[i] = c;
	}
}
