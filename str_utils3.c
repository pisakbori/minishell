/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:37:40 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/01 15:38:38 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	protect_special_chars(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\'')
			str[i] = SINGLE_QUOTE;
		if (str[i] == '\"')
			str[i] = DOUBLE_QUOTE;
		if (str[i] == '>')
			str[i] = GREATER_THAN;
		if (str[i] == '<')
			str[i] = SMALLER_THAN;
	}
}

void	replace_special_chars(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == SINGLE_QUOTE)
			str[i] = '\'';
		if (str[i] == DOUBLE_QUOTE)
			str[i] = '\"';
		if (str[i] == GREATER_THAN)
			str[i] = '>';
		if (str[i] == SMALLER_THAN)
			str[i] = '<';
	}
}

char	*remove_all_chars(char *str, char *to_remove)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	len = 0;
	i = -1;
	while (str && str[++i])
		if (!ft_strchr(to_remove, str[i]))
			len++;
	res = ft_calloc(len + 1, 1);
	i = -1;
	j = 0;
	while (str && str[++i])
	{
		if (!ft_strchr(to_remove, str[i]))
			res[j++] = str[i];
	}
	return (res);
}
