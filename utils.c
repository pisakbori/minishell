/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:16:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/03 12:09:22 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ends_with_char(char *str, char c)
{
	return (str && *str && str[ft_strlen(str) - 1] == c);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*ret;

	if (str == 0)
		return (0);
	ret = (char *)malloc(n + 1);
	if (ret == 0)
		return (0);
	i = -1;
	while (++i < n)
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

int	str_equal(char *str1, char *str2)
{
	int	len1;
	int	len2;

	if (!str1 && !str2)
		return (1);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 != len2)
		return (0);
	return (!ft_strncmp(str1, str2, len1));
}

char	*found_variable(int name_len, char *line)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line_len == name_len)
		return (NULL);
	if (line[name_len] == '=')
		return (ft_strndup(line + name_len + 1, line_len - name_len));
	return (NULL);
}

char	*get_env_variable(char *var_name, char **env)
{
	int	i;
	int	name_len;

	i = -1;
	name_len = ft_strlen((const char *)var_name);
	while (env[++i])
	{
		if (!ft_strncmp(var_name, env[i], name_len))
			return (found_variable(name_len, env[i]));
	}
	return (NULL);
}

void	set_error(char *text, int err_code)
{
	// TODO: set last errorcode to err_code
	(void)err_code;
	ft_printf(2, "minishell: %s: ", text);
	perror(NULL);
}

int	is_delim(char const *s, char *delim)
{
	return (ft_strchr(delim, *s) != NULL);
}

static int	is_start_of_word(int i, char const *s, char *delim)
{
	if (i == 0)
		return (!is_delim(s, delim));
	else
		return (!is_delim(s, delim) && is_delim(s - 1, delim));
}

static int	count_words(char *s, char *delim)
{
	int	num_words;
	int	i;

	i = 0;
	num_words = 0;
	while (*(s + i))
	{
		if (is_start_of_word(i, s + i, delim))
			num_words++;
		else if (is_delim(s + i, delim))
			num_words++;
		i++;
	}
	return (num_words);
}

static char	*dup_word(char const *s, char *c)
{
	char	*end;
	char	*start;
	char	*word;

	start = (char *)s;
	while (*s && !is_delim(s, c))
		s++;
	end = (char *)s;
	word = ft_substr(start, 0, end - start);
	return (word);
}

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

//TODO: 2 level split. ex: a1 a2 a3 | b1 b2 ; c1 c2 | d1 | e1
// a1 a2 a3 0
// | 0
// b1 b2 0
// ; 0
// c1 c2 0
// | 0
// d1 0
// | 0
// e1 0
char	**ft_split_and_keep(char const *s, char *delim)
{
	int		num_words;
	char	**res;
	char	**iter;
	int		i;

	i = 0;
	num_words = count_words((char *)s, delim);
	res = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!res)
		return (NULL);
	*(res + num_words) = 0;
	iter = res;
	while (*(s + i))
	{
		if (is_start_of_word(i, s + i, delim))
		{
			*iter = dup_word(s + i, delim);
			if (!*iter)
				return (split_collect_garbage(res, iter - res));
			iter++;
		}
		else if (s[i] == '|')
		{
			*iter = ft_strdup("|");
			if (!*iter)
				return (split_collect_garbage(res, iter - res));
			iter++;
		}
		else if (s[i] == ';')
		{
			*iter = ft_strdup(";");
			if (!*iter)
				return (split_collect_garbage(res, iter - res));
			iter++;
		}
		i++;
	}
	return (res);
}
