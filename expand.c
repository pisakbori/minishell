/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:25:04 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/17 11:06:00 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*operation_map(char *str)
{
	char	*res;
	int		i;

	// char	*p;
	i = -1;
	res = ft_calloc(1, ft_strlen(str) + 1);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			res[i] = 'k';
	}
	// p = ft_strchr(str, '\'');
	// if (p)
	// 	p = ft_strchr(p, '\'');
	return (res);
}

char	*expand_variables(char *str)
{
	printf("%s\n", str);
	printf("%s\n", operation_map(str));
	return (str);
}