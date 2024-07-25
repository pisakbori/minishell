/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:59:46 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 16:56:03 by bpisak-l         ###   ########.fr       */
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
	int		out_mode;
	mode_t	rights;

	rights = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	m_dup2(state()->backup_stdin, STDIN_FILENO);
	m_dup2(state()->backup_stdout, STDOUT_FILENO);
	if (s->redir.invalid)
		return ;
	if (s->redir.in)
	{
		s->redir.in_fd = open(s->redir.in, O_RDONLY, S_IRWXU);
		if (s->redir.in_fd != -1)
			m_dup2(s->redir.in_fd, STDIN_FILENO);
		close(s->redir.in_fd);
	}
	if (s->redir.out)
	{
		out_mode = O_CREAT | O_WRONLY | s->redir.out_mode;
		s->redir.out_fd = open(s->redir.out, out_mode, rights);
		if (s->redir.out_fd != -1)
			m_dup2(s->redir.out_fd, STDOUT_FILENO);
		close(s->redir.out_fd);
	}
}
