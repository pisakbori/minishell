/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:53:54 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/01 15:38:44 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ends_with_char(char *str, char c)
{
	return (str && *str && str[ft_strlen(str) - 1] == c);
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
		if (map[i] == DELIMITER)
			str[i] = c;
	}
}

char	*skip_until(char c, char *s)
{
	char	*next;

	if (*s == c)
	{
		if (!*(s + 1))
			return (s + 1);
		next = ft_strchr(s + 1, c);
		return (next);
	}
	return (s);
}

int	chars_freq(char *str, char *chars)
{
	int	freq;
	int	i;

	if (!str || !chars || !*str || !*chars)
		return (0);
	freq = 0;
	i = -1;
	while (str[++i])
		if (str_has(chars, str[i]))
			freq++;
	return (freq);
}

int	char_freq(char *str, char c)
{
	int	freq;
	int	i;

	if (!str || !c || !*str)
		return (0);
	freq = 0;
	i = -1;
	while (str[++i])
		if (str[i] == c)
			freq++;
	return (freq);
}
