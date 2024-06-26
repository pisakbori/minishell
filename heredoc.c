/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:08:42 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/26 09:35:04 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(char *key)
{
	ft_printf(state()->backup_stdout, "HEREDOC with key %s\n", key);
}

char	**parse_heredoc(char *str, int index)
{
	char *map;
	char **parts;
	char **res;
	int i;

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
		else if (is_unsplit_heredoc(parts[i]))
			add_unsplit_heredoc(parts[i], map, i, index);
		else
			map[i] = KEEP;
	}
	res = keep_nonredir_only(map, parts);
	free(map);
	free_split_arr(parts);
	return (res);
}