/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:38:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/17 22:29:11 by bpisak-l         ###   ########.fr       */
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

static int	is_delim(char s, char *delim)
{
	return (ft_strchr(delim, s) != NULL);
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

int	set_zeros(char *s, char *delim, int *num_words)
{
	*num_words = 0;
	if (!s)
		return (0);
	if (!(*s))
		return (1);
	while (*s)
	{
		s = skip_quote('"', s);
		if (!s)
			return (0);
		else if (!*s)
			break ;
		s = skip_quote('\'', s);
		if (!s)
			return (0);
		else if (!*s)
			break ;
		if (is_delim(*s, delim))
			*s = 0;
		if (!*s && *(s - 1))
			*num_words += 1;
		s++;
	}
	if (*(s - 1))
		*num_words += 1;
	return (1);
}

int	is_empty_word(char *s)
{
	if (s[0] == ('"') && s[1] == ('"') && !s[2])
		return (1);
	else
		return (0);
}

int	add_new_word(char **res, int index, char *word, int *j, char mode)
{
	printf("new word >%s<\n", word);
	if (mode)
		res[index] = ft_strdup(word);
	else
		res[index] = expand_variables(word);
	if (!res[index])
	{
		free(word);
		return (split_collect_garbage(res, index));
	}
	*j += ft_strlen(word);
	return (1);
}

void	skip_delimiters(char *str, int *j)
{
	while (!str[*j])
		*j += 1;
}

char	**ft_split2(char *s, char *delim, char mode)
{
	char	*clone;
	char	**res;
	int		i;
	int		j;
	int		len;

	clone = ft_strdup(s);
	len = ft_strlen(clone);
	set_zeros(clone, delim, &i);
	if (!i)
		return (NULL);
	res = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (j < len)
	{
		skip_delimiters(clone, &j);
		if (j == len)
			break ;
		if (!add_new_word(res, ++i, clone + j, &j, mode))
			return (NULL);
		j++;
	}
	free(clone);
	return (res);
}
