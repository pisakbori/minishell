/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:56:48 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/19 09:39:37 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redir(int index, char mode, char *filename, char io)
{
	int	fd;

	if (io == IN)
	{
		get_state()->redirs[index].in_mode = mode;
		get_state()->redirs[index].in = filename;
	}
	if (io == OUT)
	{
		get_state()->redirs[index].out_mode = mode;
		get_state()->redirs[index].out = filename;
		printf("here1\n");
		if (mode == TRUNCATE)
			fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		else if (mode == APPEND)
			fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (fd == -1)
			set_error(NULL, 1, "open");
		close(fd);
		printf("here2\n");
	}
}

void	add_separated_redir(char *symbol, char *arg, char *map, int i)
{
	if (str_equal(symbol, "<"))
		add_redir(i, TRUNCATE, arg, IN);
	else if (str_equal(symbol, "<<"))
		add_redir(i, APPEND, arg, IN);
	else if (str_equal(symbol, ">"))
		add_redir(i, TRUNCATE, arg, OUT);
	else if (str_equal(symbol, ">>"))
		add_redir(i, APPEND, arg, OUT);
	// printf("here: %d, redir: %s %s \n", index, get_state()->redirs[index].in,
	// 		get_state()->redirs[index].out);
	*map = SKIP;
	*(map + 1) = SKIP;
}

void	add_unsplit_redir(char *str, char *map, int j, int index)
{
	char	*arg;

	arg = get_arg_name(str);
	if (starts_with(str, "<<"))
		add_redir(index, APPEND, arg, IN);
	else if (starts_with(str, "<"))
		add_redir(index, TRUNCATE, arg, IN);
	else if (starts_with(str, ">>"))
		add_redir(index, APPEND, arg, OUT);
	else if (starts_with(str, ">"))
		add_redir(index, TRUNCATE, arg, OUT);
	map[j] = SKIP;
	// printf("here: %d, redir: %s %s \n", index, get_state()->redirs[index].in,
	// 		get_state()->redirs[index].out);
}

char	**keep_nonredir_only(char *map, char **parts)
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

/// @brief splits str by spaces and remove everything related to redirection
/// @param str
/// @param index
/// @return
char	**parse_redir(char *str, int index)
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
		if (is_separated_redir(parts[i], parts[i + 1]))
		{
			add_separated_redir(parts[i], parts[i + 1], map + i, index);
			i++;
		}
		else if (is_unsplit_redir(parts[i]))
			add_unsplit_redir(parts[i], map, i, index);
		else
			map[i] = KEEP;
	}
	res = keep_nonredir_only(map, parts);
	free(map);
	free_split_arr(parts);
	return (res);
}
