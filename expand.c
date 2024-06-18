/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:25:04 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/17 22:22:57 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*operation_map(char *str)
{
	char	*res;
	char	*next_q;
	int		i;
	int		j;

	i = -1;
	res = ft_calloc(1, ft_strlen(str) + 1);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			res[i] = '-';
			j = i;
			next_q = skip_quote(str[i], str + i);
			i = next_q - str;
			while (++j < i)
				res[j] = *next_q;
			res[j] = '-';
		}
		else
			res[i] = 'k';
	}
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

int	start_variable(char *str, char *map, int i)
{
	int	res;

	res = 1;
	res = res && map[i] != '\'';
	res = res && str[i] == '$';
	res = res && str[i + 2];
	res = res && (ft_isalnum(str[i + 2]) || str[i + 2] == '_');
	return (res);
}

char	*expand_env_var_name(char *until, char *str, int j)
{
	char	*value;
	char	temp;
	char	*var_name;

	temp = *until;
	*until = 0;
	var_name = ft_strdup(str + j);
	*until = temp;
	value = get_env_variable(var_name);
	return (value);
}

char	*end_variable_name(char *str)
{
	if (ft_isdigit(*str))
		return (str + 1);
	else
		return (next_nonalpha(str + 1));
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

int	append_variable_value(char **res, char **buff, char *str, int *i)
{
	char	*value;
	char	*until;

	*res = ft_str_append(*res, *buff);
	*buff = ft_calloc(1, ft_strlen(str) + 1);
	until = end_variable_name(str + *i + 1);
	if (until)
		value = expand_env_var_name(until, str, *i + 1);
	*res = ft_str_append(*res, value);
	*i = until - str - 1;
	return (0);
}

char	*expand_variables(char *str)
{
	char	*map;
	char	*res;
	int		i;
	int		j;
	char	*buff;

	map = operation_map(str);
	i = 0;
	j = 0;
	res = NULL;
	buff = ft_calloc(1, ft_strlen(str) + 1);
	while (map[i])
	{
		if (start_variable(str, map, i))
		{
			j = 0;
			append_variable_value(&res, &buff, str, &i);
		}
		else if (map[i] != '-')
			buff[j++] = str[i];
		i++;
	}
	res = ft_str_append(res, buff);
	buff = ft_calloc(1, ft_strlen(str) + 1);
	return (res);
}
