/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:38:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/12 10:12:43 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	**split_collect_garbage(char **res, int i)
{
	while (i >= 0)
	{
		free(*(res + i));
		i--;
	}
	free(res);
	return (NULL);
}

static int	is_delim(char s, char *delim)
{
	return (ft_strchr(delim, s) != NULL);
}

void	set_zeros(char *s, char *delim, int *num_words)
{
	char	*next_quote;

	*num_words = 0;
	if (!s || !(*s))
		return ;
	while (*s)
	{
		if (*s == '"')
		{
			next_quote = ft_strchr(s + 1, '"') + 1;
			if (next_quote - 2 == s)
			{
				*s = 0;
				*(s + 1) = 0;
			}
			s = next_quote;
		}
		if (is_delim(*s, delim))
			*s = 0;
		if (!*s && *(s - 1))
			*num_words += 1;
		s++;
	}
	if (*(s - 1))
		*num_words += 1;
}

char	**ft_split2(char *s, char *delim)
{
	int len;
	char *clone;
	char **res;
	int num_words;
	int i;

	len = ft_strlen(s);
	clone = ft_strdup(s);
	set_zeros(clone, delim, &num_words);
	res = ft_calloc(num_words + 1, sizeof(char *));
	i = -1;
	while (++i < num_words)
	{
		res[i] = ft_strdup(clone);
		if (!res[i])
			return (split_collect_garbage(res, i));
		clone += ft_strlen(res[i]) + 1;
	}
	return (res);
}