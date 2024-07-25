/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:58:06 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 15:46:36 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_redirs(char *token1, char *name, int index)
{
	char	*fn;

	if (!state()->pipeline[index].redir.invalid)
	{
		fn = get_filename(name, index);
		if (str_equal(token1, "<"))
			add_i_redir(index, SINGLE, fn);
		else if (str_equal(token1, ">"))
			add_o_redir(index, O_TRUNC, fn);
		else if (str_equal(token1, ">>"))
			add_o_redir(index, O_APPEND, fn);
	}
}

void	set_redir_name(char *name, char *map, int *i, char *str)
{
	int	k;

	k = 0;
	while ((map[*i] != KEEP || (str[*i] != '>' && str[*i] != '<')))
	{
		if (!str[*i])
			break ;
		if (map[*i] == KEEP && ft_is_space(str[*i]))
			break ;
		name[k] = str[*i];
		*i = *i + 1;
		k++;
	}
	name[k] = 0;
}

static int	process_token(char *str, int *i, char *map, int index)
{
	char	name[500];
	char	token1[8];

	try_get_token(token1, str, i);
	if (token1[0])
	{
		while (str[*i] && ft_is_space(str[*i]) && map[*i] == KEEP)
			*i = *i + 1;
		set_redir_name(name, map, i, str);
		set_redirs(token1, name, index);
		return (1);
	}
	return (0);
}

char	*handle_redirs(char *str, int index)
{
	int		i;
	int		j;
	char	*map;
	char	*to_keep;

	i = 0;
	j = 0;
	if (!str || *str == 0)
		return (m_ft_strdup(str));
	to_keep = m_ft_calloc(ft_strlen(str) + 1, 1);
	map = operation_map(str, NULL, "\'\"");
	while (map && str[i])
	{
		while (map[i + 1] && map[i] != KEEP)
			to_keep[j++] = str[i++];
		if (!process_token(str, &i, map, index))
			to_keep[j++] = str[i++];
	}
	free(map);
	return (to_keep);
}
