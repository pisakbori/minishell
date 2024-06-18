/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:08:41 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/18 15:22:06 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*operation_map(char *str, char *delim, char *skip)
{
	char	*res;
	char	*next_q;
	int		i;
	int		j;

	i = -1;
	res = ft_calloc(1, ft_strlen(str) + 1);
	while (str[++i])
	{
		if (ft_strchr(skip, str[i]))
		{
			res[i] = '-';
			j = i;
			next_q = skip_quote(str[i], str + i);
			i = next_q - str;
			while (++j < i)
				res[j] = *next_q;
			res[j] = '-';
		}
		else if (!str_contains(str[i], delim))
			res[i] = 'k';
		else
			res[i] = 'd';
	}
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

char	*end_variable_name(char *str)
{
	if (ft_isdigit(*str))
		return (str + 1);
	else
		return (next_nonalpha(str + 1));
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
