/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:38:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/12 11:41:37 by bpisak-l         ###   ########.fr       */
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
			// if (next_quote - 2 == s)
			// {
			// 	*s = 0;
			// 	*(s + 1) = 0;
			// }
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

int	is_empty_word(char *s)
{
	if (s[0] == ('"') && s[1] == ('"') && !s[2])
		return (1);
	else
		return (0);
}

char	**ft_split2(char *s, char *delim)
{
	char	*clone;
	char	**res;
	int		i;
	int		j;
	int		len;

	clone = ft_strdup(s);
	len = ft_strlen(clone);
	set_zeros(clone, delim, &i);
	res = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (j < len)
	{
		while (!clone[j])
			j++;
		if (j < len - 1 && !is_empty_word(clone + j))
		{
			res[++i] = ft_strdup(clone + j);
			if (!res[i])
				return (split_collect_garbage(res, i));
			j += ft_strlen(res[i]) + 1;
		}
		else
			j += 3;
	}
	return (res);
}
