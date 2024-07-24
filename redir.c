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
