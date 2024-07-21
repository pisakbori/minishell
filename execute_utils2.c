/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:59:46 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/21 18:07:16 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_redir(t_stage stage)
{
	if (stage.redir.in_fd && stage.redir.in_fd != -1)
		close(stage.redir.in_fd);
	if (stage.redir.out_fd && stage.redir.out_fd != -1)
		close(stage.redir.out_fd);
}

void	close_all_redir(void)
{
	t_stage	*pipeline;

	pipeline = state()->pipeline;
	while (pipeline->argv)
	{
		if (pipeline->redir.in_fd || pipeline->redir.out_fd)
			close_redir(*pipeline);
		pipeline++;
	}
}

void	handle_redir(t_stage *s)
{
	int	out_mode;

	reset_stdio();
	if (s->redir.invalid)
		return ;
	if (s->redir.in)
	{
		s->redir.in_fd = open(s->redir.in, O_RDONLY, S_IRWXU);
		if (s->redir.in_fd != -1)
		{
			dup2(s->redir.in_fd, STDIN_FILENO);
			close(s->redir.in_fd);
			// if (s->redir.in_mode == DOUBLE)
			// 	unlink(s->redir.in);
		}
	}
	if (s->redir.out)
	{
		out_mode = O_CREAT | O_WRONLY | s->redir.out_mode;
		s->redir.out_fd = open(s->redir.out, out_mode, S_IRWXU);
		if (s->redir.out_fd != -1)
			dup2(s->redir.out_fd, STDOUT_FILENO);
		close(s->redir.out_fd);
	}
}
