/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:26:08 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/01 14:16:12 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	invalid_pipe(void)
{
	t_pipe	p;

	p.read = -1;
	p.write = -1;
	return (p);
}

void	close_pipe(t_pipe *p)
{
	close_read(p);
	close_write(p);
}

void	close_read(t_pipe *p)
{
	if (p && p->read != -1)
		close(p->read);
}

void	close_write(t_pipe *p)
{
	if (p && p->write != -1)
		close(p->write);
}

int	pipeline_len(t_stage *pipeline)
{
	int	len;

	len = 0;
	if (!pipeline)
		return (0);
	while (pipeline[len].argv)
		len++;
	return (len);
}
