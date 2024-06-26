/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:08:42 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/26 14:09:01 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_heredoc(char *str, int index)
{
	char	*map;
	char	**parts;
	char	**res;
	int		i;

	i = -1;
	parts = str_split(str, " \t", "\"\'");
	map = ft_calloc(ft_arr_len(parts) + 1, 1);
	while (parts[++i])
	{
		if (is_separated_heredoc(parts[i], parts[i + 1]))
		{
			add_separated_heredoc(parts[i + 1], map + i, index);
			i++;
		}
		else if (starts_with(parts[i], "<<"))
			add_unsplit_heredoc(parts[i], map, i, index);
		else
			map[i] = KEEP;
	}
	res = keep_marked_only(map, parts);
	free(map);
	free_split_arr(parts);
	return (str_join_all(res, " "));
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
