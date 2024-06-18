/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:38:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/18 12:55:23 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	split_collect_garbage(char **res, int i)
{
	while (i >= 0)
	{
		free(*(res + i));
		i--;
	}
	free(res);
	return (0);
}

int	str_contains(char c, char *str)
{
	return (ft_strchr(str, c) != NULL);
}

char	*skip_quote(char quote_type, char *s)
{
	char	*next_quote;

	if (*s == quote_type)
	{
		if (!*(s + 1))
			return (s + 1);
		next_quote = ft_strchr(s + 1, quote_type);
		return (next_quote);
	}
	return (s);
}

int	is_empty_word(char *s)
{
	if (s[0] == ('"') && s[1] == ('"') && !s[2])
		return (1);
	else
		return (0);
}

void	skip_delimiters(char *str, int *j)
{
	while (!str[*j])
		*j += 1;
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

int	is_word_start(char *map, int i)
{
	return ((!i || map[i - 1] == 'd') && map[i] != 'd');
}

char	**ft_split2(char *s, char *delim, char *skip)
{
	char	*map;
	int		i;
	int		j;
	char	*clone;
	char	**res;
	int		words;

	i = -1;
	words = 0;
	map = operation_map(s, delim, skip);
	clone = ft_strdup(s);
	ft_replace_chars(clone, map, 0);
	// printf("%s\n%s\n", s, map);
	while (map[++i])
	{
		if (is_word_start(map, i))
			words++;
	}
	res = ft_calloc(words + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (map[++i])
	{
		if (is_word_start(map, i))
		{
			res[j++] = ft_strdup(clone + i);
			if (!res[j - 1])
			{
				split_collect_garbage(res, j);
				break ;
			}
		}
	}
	free(clone);
	free(map);
	return (res);
}
