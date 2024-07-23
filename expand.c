/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:25:04 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/23 18:04:31 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variables(char *str, char *skip)
{
	char	*map;
	char	*res;
	int		i;
	int		j;
	char	*buff;

	map = operation_map(str, NULL, skip);
	i = 0;
	j = 0;
	res = NULL;
	buff = ft_calloc(1, ft_strlen(str) + 1);
	while (map[i])
	{
		if (str[i] && map[i] != '\'' && str[i] == '\\' && str[i + 1] == '$')
		{
			i++;
			continue ;
		}
		else if (start_variable(str, map, i))
		{
			j = 0;
			append_variable_value(&res, &buff, str, &i);
		}
		else
			buff[j++] = str[i];
		i++;
	}
	res = ft_str_append(res, buff);
	free(map);
	return (res);
}

void	arr_expand_variables(char **cmd_set)
{
	char	*temp;

	if (!cmd_set)
		return ;
	while (*cmd_set)
	{
		temp = *cmd_set;
		*cmd_set = expand_variables(*cmd_set, "\'\"");
		free(temp);
		cmd_set++;
	}
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
	res = ft_calloc(ft_strlen(map) - freq + 1, 1);
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

void	arr_remove_chars(char **cmd_set, char *skip)
{
	char	*temp;

	if (!cmd_set)
		return ;
	while (*cmd_set)
	{
		temp = *cmd_set;
		*cmd_set = remove_chars(*cmd_set, skip);
		free(temp);
		cmd_set++;
	}
}
