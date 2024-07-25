/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:25:04 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 14:01:10 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	escape_dollar(char *str, int i, char *map)
{
	int	res;

	if (!str[i])
		return (0);
	res = map[i] != '\'' && str[i] == '\\' && str[i + 1] == '$';
	return (res);
}

char	*expand_variables(char *str, char *skip)
{
	char	*map;
	char	*res;
	int		i;
	int		j;
	char	*buff;

	map = operation_map(str, NULL, skip);
	i = -1;
	j = 0;
	res = NULL;
	buff = m_ft_calloc(1, ft_strlen(str) + 1);
	while (map[++i])
	{
		if (str[i] && map[i] != '\'' && str[i] == '\\' && str[i + 1] == '\\')
			buff[j++] = str[i++];
		else if (!escape_dollar(str, i, map) && start_variable(str, map, i))
		{
			j = 0;
			append_variable_value(&res, &buff, str, &i);
		}
		else if (!escape_dollar(str, i, map))
			buff[j++] = str[i];
	}
	free(map);
	return (ft_str_append(res, buff));
}

char	*remove_chars(char *str, char *skip)
{
	char	*map;
	int		i;
	int		j;
	int		freq;
	char	*res;

	map = operation_map(str, NULL, skip);
	freq = chars_freq(map, "-");
	res = m_ft_calloc(ft_strlen(map) - freq + 1, 1);
	i = -1;
	j = 0;
	while (map[++i])
	{
		if (map[i] != SKIP)
			res[j++] = str[i];
	}
	free(map);
	return (res);
}
