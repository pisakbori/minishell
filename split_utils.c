/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:38:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/30 18:36:03 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_word_start(char *map, int i)
{
	int	after_delim;

	after_delim = !i || map[i - 1] == DELIMITER;
	return (after_delim && map[i] != DELIMITER);
}

char	**init_words(char *map)
{
	int		words;
	int		i;
	char	**res;

	words = 0;
	i = -1;
	while (map[++i])
	{
		if (is_word_start(map, i))
			words++;
	}
	res = ft_calloc(words + 1, sizeof(char *));
	return (res);
}

char	*set_delim_zeros(char *map, char *s)
{
	char	*clone;

	clone = ft_strdup(s);
	ft_replace_chars(clone, map, 0);
	return (clone);
}

char	**str_split(char *s, char *delim, char *skip)
{
	char	*map;
	int		i;
	int		j;
	char	*clone;
	char	**res;

	map = operation_map(s, delim, skip);
	clone = set_delim_zeros(map, s);
	res = init_words(map);
	i = -1;
	j = 0;
	while (map[++i])
	{
		if (is_word_start(map, i))
		{
			res[j++] = ft_strdup(clone + i);
			if (!res[j - 1])
				return (split_fail_free(res, j, map, clone));
		}
	}
	free(clone);
	free(map);
	return (res);
}
