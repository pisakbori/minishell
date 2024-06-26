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

void	add_i_redir(int index, int mode, char *filename)
{
	char	*fn;

	if (state()->pipeline[index].redir.invalid)
		return ;
	fn = remove_chars(filename, "\"\'");
	if (!path_exists(fn))
	{
		set_mini_error(fn, 1, "No such file or directory");
		state()->pipeline[index].redir.invalid = 1;
	}
	else if (path_exists(fn) && access(fn, R_OK))
	{
		set_error("minishell", 1, "Permission denied");
		state()->pipeline[index].redir.invalid = 1;
	}
	else
	{
		state()->pipeline[index].redir.in_mode = mode;
		if (state()->pipeline[index].redir.in)
			free(state()->pipeline[index].redir.in);
		state()->pipeline[index].redir.in = fn;
	}
}

void	create_heredoc(int index, char *key1)
{
	char	*key;
	char	*temp;
	char	*hd_line;
	char	*heredoc_name;
	int		fd;

	hd_line = NULL;
	heredoc_name = ft_strdup("heredoc");
	temp = heredoc_name;
	heredoc_name = ft_strjoin(heredoc_name, ft_itoa(index));
	free(temp);
	temp = heredoc_name;
	heredoc_name = ft_path_join(state()->heredoc_dir, heredoc_name);
	free(temp);
	key = remove_chars(key1, "\"\'");
	fd = open(heredoc_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	while (1)
	{
		hd_line = readline("> ");
		if (!hd_line || str_equal(hd_line, key))
			break ;
		ft_printf(fd, hd_line);
		ft_printf(fd, "\n");
	}
	close(fd);
	add_i_redir(index, DOUBLE, heredoc_name);
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

void	add_o_redir(int index, int mode, char *filename)
{
	int		fd;
	int		w_mode;
	char	*fn;

	if (state()->pipeline[index].redir.invalid)
		return ;
	fn = remove_chars(filename, "\"\'");
	if (mode == SINGLE)
		w_mode = O_TRUNC;
	else
		w_mode = O_APPEND;
	if (path_exists(fn) && access(fn, W_OK))
	{
		set_error("minishell", 1, "Permission denied");
		state()->pipeline[index].redir.invalid = 1;
	}
	else
	{
		fd = open(fn, O_CREAT | O_WRONLY | w_mode, S_IRWXU);
		close(fd);
		if (fd != -1)
		{
			if (state()->pipeline[index].redir.out)
				free(state()->pipeline[index].redir.out);
			state()->pipeline[index].redir.out_mode = mode;
			state()->pipeline[index].redir.out = fn;
		}
		else
		{
			set_mini_error(fn, 1, "No such file or directory");
			state()->pipeline[index].redir.invalid = 1;
		}
	}
}

void	add_separated_redir(char *symbol, char *arg, char *map, int i)
{
	if (str_equal(symbol, "<"))
		add_i_redir(i, SINGLE, arg);
	else if (str_equal(symbol, ">"))
		add_o_redir(i, SINGLE, arg);
	else if (str_equal(symbol, ">>"))
		add_o_redir(i, DOUBLE, arg);
	*map = SKIP;
	*(map + 1) = SKIP;
}

void	add_unsplit_redir(char *str, char *map, int j, int index)
{
	char	*arg;

	arg = get_arg_name(str);
	if (starts_with(str, "<"))
		add_i_redir(index, SINGLE, arg);
	else if (starts_with(str, ">>"))
		add_o_redir(index, DOUBLE, arg);
	else if (starts_with(str, ">"))
		add_o_redir(index, SINGLE, arg);
	map[j] = SKIP;
}

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
	res = keep_marked_only(map, parts);
	free(map);
	free_split_arr(parts);
	return (res);
}
