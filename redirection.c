/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:58:06 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 09:26:14 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_redirs(char *str, int index)
{
	int		i;
	int		j;
	int		k;
	char	token1[8];
	char	name[500];
	char	*map;
	char	*to_keep;
	char	*fn;

	i = 0;
	j = 0;
	if (!str || *str == 0)
		return (ft_strdup(str));
	to_keep = ft_calloc(ft_strlen(str) + 1, 1);
	map = operation_map(str, NULL, "\'\"");
	while (map && str[i])
	{
		while (map[i + 1] && map[i] != KEEP)
		{
			to_keep[j++] = str[i];
			i++;
		}
		try_get_token(token1, str, &i);
		if (token1[0])
		{
			while (str[i] && ft_is_space(str[i]) && map[i] == KEEP)
				i++;
			k = 0;
			while (str[i] && (map[i] != KEEP || (str[i] != '>' && str[i] != '<'
						&& !ft_is_space(str[i]))))
			{
				name[k] = str[i];
				i++;
				k++;
			}
			name[k] = 0;
			fn = get_filename(name, index);
			if (str_equal(token1, "<"))
				add_i_redir(index, SINGLE, fn);
			else if (str_equal(token1, ">"))
				add_o_redir(index, O_TRUNC, fn);
			else if (str_equal(token1, ">>"))
				add_o_redir(index, O_APPEND, fn);
		}
		else
		{
			to_keep[j++] = str[i];
			i++;
		}
	}
	to_keep[j] = 0;
	free(map);
	return (to_keep);
}
