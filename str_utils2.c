/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:53:54 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 16:14:35 by bpisak-l         ###   ########.fr       */
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

char	*ft_path_join(char *path, char *bin_name)
{
	char	*temp;
	char	*full_path;

	if (!ends_with_char(path, '/') && (bin_name[0] != '/'))
	{
		temp = m_ft_strjoin(path, "/");
		full_path = m_ft_strjoin(temp, bin_name);
		free(temp);
	}
	else
		full_path = m_ft_strjoin(path, bin_name);
	return (full_path);
}
