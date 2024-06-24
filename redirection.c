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

void	add_redir(int index, int mode, char *filename, char io)
{
	int	fd;

	if (io == IN)
	{
		state()->pipeline[index].redir.in_mode = 0 | mode;
		state()->pipeline[index].redir.in = filename;
	}
	if (io == OUT)
	{
		state()->pipeline[index].redir.out_mode = 0 | mode;
		state()->pipeline[index].redir.out = filename;
		fd = 0;
		if (path_exists(filename) && access(filename, W_OK))
			set_error(NULL, 1, "Permission denied");
		else
			fd = open(filename, O_CREAT | O_WRONLY | mode, S_IRWXU);
		if (fd == -1)
			set_error(NULL, 1, "Permission denied");
		else
			close(fd);
	}
}

void	add_separated_redir(char *symbol, char *arg, char *map, int i)
{
	if (str_equal(symbol, "<"))
		add_redir(i, O_APPEND, arg, IN);
	else if (str_equal(symbol, "<<"))
		add_redir(i, O_TRUNC, arg, IN);
	else if (str_equal(symbol, ">"))
		add_redir(i, O_TRUNC, arg, OUT);
	else if (str_equal(symbol, ">>"))
		add_redir(i, O_APPEND, arg, OUT);
	*map = SKIP;
	*(map + 1) = SKIP;
}

void	add_unsplit_redir(char *str, char *map, int j, int index)
{
	char	*arg;

	arg = get_arg_name(str);
	if (starts_with(str, "<<"))
		add_redir(index, O_APPEND, arg, IN);
	else if (starts_with(str, "<"))
		add_redir(index, O_TRUNC, arg, IN);
	else if (starts_with(str, ">>"))
		add_redir(index, O_APPEND, arg, OUT);
	else if (starts_with(str, ">"))
		add_redir(index, O_TRUNC, arg, OUT);
	map[j] = SKIP;
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
