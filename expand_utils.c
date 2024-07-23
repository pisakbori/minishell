/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:08:41 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/23 14:47:25 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/// @brief Creates a map corresponding to str used for split
/// @param str original str, anything to be kept -> 'k'
/// @param skip
// characters in 				"skip"->SKIP,
// anything between a pair of  "skip" -> the skipped char
/// @param delim characters in 	delimiter	"delim"-> DELIMITER,
/// @return map
char	*operation_map(char *str, char *delim, char *skip)
{
	char	*res;
	char	*next;
	int		i;
	int		j;

	i = -1;
	if (!str)
		return (NULL);
	res = ft_calloc(1, ft_strlen(str) + 1);
	while (str[++i])
	{
		if (ft_strchr(skip, str[i]))
		{
			res[i] = SKIP;
			j = i;
			next = skip_until(str[i], str + i);
			i = next - str;
			while (++j < i)
				res[j] = *next;
			res[j] = SKIP;
		}
		else if (delim == NULL || !str_has(delim, str[i]))
			res[i] = KEEP;
		else
			res[i] = DELIMITER;
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
	if (str_equal(var_name, "?"))
		value = ft_strdup(ft_itoa(state()->exit_code));
	else if (str_equal(var_name, "_"))
		value = ft_strdup(state()->last_arg);
	else
	{
		value = get_env_variable(var_name);
		protect_special_chars(value);
	}
	free(var_name);
	return (value);
}

int	start_variable(char *str, char *map, int i)
{
	int	res;
	int	is_variable_start;

	res = 1;
	is_variable_start = 0;
	res = res && map[i] != '\'';
	res = res && str[i] == '$';
	res = res && str[i + 1];
	is_variable_start = is_variable_start || ft_isalnum(str[i + 1]);
	is_variable_start = is_variable_start || (str[i + 1] == '\'');
	is_variable_start = is_variable_start || (str[i + 1] == '"');
	is_variable_start = is_variable_start || str_has("_?", str[i + 1]);
	res = res && is_variable_start;
	return (res);
}

char	*end_variable_name(char *str)
{
	if ((*str == '"') || (*str == '\''))
		return (str);
	if (ft_isdigit(*str) || (*str == '?'))
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
	value = NULL;
	if (until)
		value = expand_env_var_name(until, str, *i + 1);
	*res = ft_str_append(*res, value);
	*i = until - str - 1;
	return (0);
}
