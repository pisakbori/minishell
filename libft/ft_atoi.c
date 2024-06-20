/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:51:31 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/20 12:09:26 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	char	*spaces;

	spaces = "\t\n\v\f\r ";
	while (*spaces)
	{
		if (*spaces == c)
			return (1);
		spaces++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	sign;

	res = 0;
	i = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	else if (str[i] == '+')
		i++;
	if (str[i] == '0')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + sign * (str[i] - '0');
		i++;
	}
	return (res);
}
