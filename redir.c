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

void	add_i_redir(int index, int mode, char *fn)
{
	if (access(fn, F_OK))
	{
		set_mini_error(fn, 1, "No such file or directory");
		state()->pipeline[index].redir.invalid = 1;
	}
	if (!access(fn, F_OK) && access(fn, R_OK))
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
		return ;
	}
	free(fn);
}

void	add_o_redir(int index, int mode, char *fn)
{
	int		fd;
	mode_t	rights;

	rights = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (!access(fn, F_OK) && access(fn, W_OK))
	{
		set_error("minishell", 1, "Permission denied");
		state()->pipeline[index].redir.invalid = 1;
	}
	else
	{
		fd = open(fn, O_CREAT | O_WRONLY | mode, rights);
		close(fd);
		if (fd != -1)
		{
			if (state()->pipeline[index].redir.out)
				free(state()->pipeline[index].redir.out);
			state()->pipeline[index].redir.out_mode = mode;
			state()->pipeline[index].redir.out = fn;
			return ;
		}
		else
		{
			set_mini_error(fn, 1, "No such file or directory");
			state()->pipeline[index].redir.invalid = 1;
		}
	}
	free(fn);
}

void	add_separated_redir(char *symbol, char *arg, char *map, int i)
{
	char	*fn;

	fn = get_filename(arg, i);
	if (!state()->pipeline[i].redir.invalid)
	{
		if (str_equal(symbol, "<"))
			add_i_redir(i, SINGLE, fn);
		else if (str_equal(symbol, ">"))
			add_o_redir(i, O_TRUNC, fn);
		else if (str_equal(symbol, ">>"))
			add_o_redir(i, O_APPEND, fn);
	}
	else
		free(fn);
	*map = SKIP;
	*(map + 1) = SKIP;
}

// TODO: free fn if open fails???
void	add_unsplit_redir(char *str, char *map, int j, int index)
{
	char	*arg;
	char	*fn;

	arg = get_arg_name(str);
	fn = get_filename(arg, index);
	if (!state()->pipeline[index].redir.invalid)
	{
		if (starts_with(str, "<"))
			add_i_redir(index, SINGLE, fn);
		else if (starts_with(str, ">>"))
			add_o_redir(index, O_APPEND, fn);
		else if (starts_with(str, ">"))
			add_o_redir(index, O_TRUNC, fn);
	}
	else
		free(fn);
	free(arg);
	map[j] = SKIP;
}

/// @brief splits str by spaces and remove everything related to redirection
/// @param str
/// @param index
/// @return
char	*handle_redirs(char *str, int index)
{
	char	*map;
	char	**parts;
	char	**res;
	char	*joined;

	parts = str_split(str, " \t", "\"\'");
	map = handle_and_mark_redirs(parts, index);
	res = keep_marked_only(map, parts);
	free(map);
	joined = str_join_all(res, " ");
	free_split_arr(res);
	free_split_arr(parts);
	return (joined);
}
