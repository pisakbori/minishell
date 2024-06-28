/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:08:42 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/27 19:31:49 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separated_heredoc(char *symbol, char *arg)
{
	return (str_equal(symbol, "<<") && is_redir_arg(arg));
}

void	add_separated_heredoc(char *arg, char *map, int i)
{
	create_heredoc(i, arg);
	*map = SKIP;
	*(map + 1) = SKIP;
}

void	add_unsplit_heredoc(char *str, char *map, int j, int i)
{
	char	*arg;

	arg = get_arg_name(str);
	create_heredoc(i, arg);
	map[j] = SKIP;
}

char	*parse_heredoc(char *str, int index)
{
	char	*map;
	char	**parts;
	char	**res;
	int		i;

	i = -1;
	parts = careful_split(str, " \t", "\"\'");
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
