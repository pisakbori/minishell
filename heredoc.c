/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:08:42 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 09:46:51 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	try_get_heredoc_token(char *token, char *str, int *i)
{
	ft_memset(token, 0, 3);
	if (!str || !str[*i] || !str[*i + 1])
		return ;
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		token[0] = '<';
		token[1] = '<';
		*i = *i + 2;
	}
}

int	name_to_keep_char(char *str, int i, char *map)
{
	int	res;

	if (!str[i])
		return (0);
	res = str[i] != '>' && str[i] != '<' && !ft_is_space(str[i]);
	res = res || map[i] != KEEP;
	return (res);
}

void	set_and_create_heredoc(char *str, int *i, char *map, int index)
{
	char	name[500];
	int		k;

	while (str[*i] && ft_is_space(str[*i]) && map[*i] == KEEP)
		*i = *i + 1;
	k = 0;
	while (name_to_keep_char(str, *i, map))
	{
		name[k] = str[*i];
		*i = *i + 1;
		k++;
	}
	name[k] = 0;
	create_heredoc(index, name);
}

char	*parse_heredoc(char *str, int index)
{
	int		i;
	int		j;
	char	token[3];
	char	*map;
	char	*to_keep;

	i = 0;
	j = 0;
	if (!str || *str == 0)
		return (ft_strdup(str));
	to_keep = ft_calloc(ft_strlen(str) + 1, 1);
	map = operation_map(str, NULL, "\'\"");
	while (map && str[i])
	{
		while (map[i + 1] && map[i] != KEEP)
			to_keep[j++] = str[i++];
		try_get_heredoc_token(token, str, &i);
		if (token[0])
			set_and_create_heredoc(str, &i, map, index);
		else
			to_keep[j++] = str[i++];
	}
	free(map);
	return (to_keep);
}

char	**handle_heredocs(char **cmd_set)
{
	int		i;
	char	**without_hd;

	without_hd = ft_calloc(ft_arr_len(cmd_set) + 1, sizeof(char *));
	i = -1;
	while (cmd_set[++i])
		without_hd[i] = parse_heredoc(cmd_set[i], i);
	return (without_hd);
}
