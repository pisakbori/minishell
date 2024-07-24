/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:08:42 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/24 16:40:45 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	try_get_heredoc_token(char *token, char *str, int *i)
{
	ft_memset(token, 0, 8);
	if (!str || !str[*i] || !str[*i + 1])
		return ;
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		token[0] = '<';
		token[1] = '<';
		*i = *i + 2;
	}
}

char	*parse_heredoc(char *str, int index)
{
	int		i;
	int		j;
	int		k;
	char	token1[8];
	char	name[500];
	char	*map;
	char	*to_keep;

	i = 0;
	j = 0;
	if (!str || *str == 0)
		return (str);
	to_keep = ft_calloc(ft_strlen(str) + 1, 1);
	map = operation_map(str, NULL, "\'\"");
	while (map && str[i])
	{
		while (map[i + 1] && map[i] != KEEP)
		{
			to_keep[j++] = str[i];
			i++;
		}
		try_get_heredoc_token(token1, str, &i);
		if (token1[0] && str_equal(token1, "<<"))
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
			create_heredoc(index, name);
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
