/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:18:08 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/04/08 17:17:04 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// count words, malloc memory for that many pointers plus null terminator
// malloc memory for each word

#include "libft.h"

static int	is_start_of_word(int i, char const *s, char c)
{
	if (i == 0)
		return (*s != c);
	else
		return (*s != c && *(s - 1) == c);
}

static int	count_words(char *s, char c)
{
	int	num_words;
	int	i;

	i = 0;
	num_words = 0;
	while (*(s + i))
	{
		if (is_start_of_word(i, s + i, c))
			num_words++;
		i++;
	}
	return (num_words);
}

static char	*dup_word(char const *s, char c)
{
	char	*end;
	char	*start;
	char	*word;

	start = (char *)s;
	while (*s && *s != c)
		s++;
	end = (char *)s;
	word = ft_substr(start, 0, end - start);
	return (word);
}

static char	**split_collect_garbage(char **res, int i)
{
	while (i >= 0)
	{
		free (*(res + i));
		i--;
	}
	free (res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		num_words;
	char	**res;
	char	**iter;
	int		i;

	i = 0;
	num_words = count_words((char *)s, c);
	res = (char **) malloc(sizeof(char *) * (num_words + 1));
	if (!res)
		return (NULL);
	*(res + num_words) = 0;
	iter = res;
	while (*(s + i))
	{
		if (is_start_of_word(i, s + i, c))
		{
			*iter = dup_word(s + i, c);
			if (!*iter)
				return (split_collect_garbage(res, iter - res));
			iter++;
		}
		i++;
	}
	return (res);
}
