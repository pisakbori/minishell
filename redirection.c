/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:56:48 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/19 09:39:37 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_bracket(char *str)
{
	int	res;

	if (!str)
		return (0);
	res = 0;
	res = res || str_equal(str, ">");
	res = res || str_equal(str, ">>");
	res = res || str_equal(str, "<");
	res = res || str_equal(str, "<<");
	return (res);
}

int	is_redir_arg(char *str)
{
	int	res;

	if (!str || !*str)
		return (0);
	res = 1;
	res = res && !starts_with(str, ">");
	res = res && !starts_with(str, "<");
	return (res);
}
int	is_unsplit_redir(char *str)
{
	int	res;
	int	err;

	if (!str || !str[0] || !str[1])
		return (0);
	res = 1;
	res = res && str_contains("><", str[0]);
	err = res && (str[0] != str[1] && str_contains("><", str[1]));
	err = err || (str_contains("><", str[1]) && str_contains("><", str[2]));
	if (err)
		set_error("minishell", 2, "syntax error near unexpected token\n");
	res = res && (str[0] == str[1] || !str_contains("><", str[1]));
	return (res);
}

int	is_separated_redir(char *symbol, char *arg)
{
	int	err;

	err = 0;
	err = err || (is_bracket(symbol) && !arg);
	err = err || (is_bracket(symbol) && is_unsplit_redir(arg));
	err = err || (is_bracket(symbol) && is_bracket(arg));
	if (err)
		set_error("minishell", 2, "syntax error near unexpected token\n");
	return (is_bracket(symbol) && is_redir_arg(arg));
}

void	add_separated_redir(char *symbol, char *arg, char *map, int j,
		int index)
{
	(void)symbol;
	(void)arg;
	(void)index;
	map[j] = '-';
	map[j + 1] = '-';
}

void	add_unsplit_redir(char *redir, char *map, int j, int index)
{
	(void)index;
	(void)redir;
	map[j] = '-';
}
char	**keep_nonredir_only(char *map, char **parts)
{
	int		len;
	char	**res;
	int		j;
	int		i;

	len = chars_freq(map, "k");
	res = ft_calloc(len + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (map[++i])
	{
		if (map[i] == 'k')
			res[j++] = ft_strdup(parts[i]);
	}
	return (res);
}

/// @brief splits str by spaces and remove everything related to redirection
/// @param str
/// @param index
/// @return
char	**parse_redir(char *str, int index)
{
	char	*map;
	char	**parts;
	char	**res;
	int		i;

	i = -1;
	parts = str_split(str, " \t", "\"\'");
	map = ft_calloc(ft_arr_len(parts) + 1, 1);
	while (parts[++i])
	{
		if (is_separated_redir(parts[i], parts[i + 1]))
		{
			add_separated_redir(parts[i], parts[i + 1], map, i, index);
			i++;
		}
		else if (is_unsplit_redir(parts[i]))
			add_unsplit_redir(parts[i], map, i, index);
		else
			map[i] = 'k';
	}
	res = keep_nonredir_only(map, parts);
	free(map);
	free_split_arr(parts);
	return (res);
}