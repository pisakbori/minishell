/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:23:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/01 15:31:40 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**keep_marked_only(char *map, char **parts)
{
	int		len;
	char	**res;
	int		j;
	int		i;

	len = char_freq(map, KEEP);
	res = ft_calloc(len + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (map[++i])
	{
		if (map[i] == KEEP)
			res[j++] = ft_strdup(parts[i]);
	}
	return (res);
}

char	*handle_and_mark_redirs(char **parts, int index)
{
	char	*map;
	int		i;

	map = ft_calloc(ft_arr_len(parts) + 1, 1);
	i = -1;
	while (parts[++i])
	{
		if (is_bracket(parts[i]) && !str_equal("<<", parts[i]))
		{
			add_separated_redir(parts[i], parts[i + 1], map + i, index);
			i++;
		}
		else if (is_unsplit_redir(parts[i]))
			add_unsplit_redir(parts[i], map, i, index);
		else
			map[i] = KEEP;
	}
	return (map);
}
