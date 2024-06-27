/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:30:32 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/27 16:01:27 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_prompt(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("^C", 1);
	// rl_redisplay();
	rl_replace_line("", 1);
	rl_redisplay();
}

// TODO:
void	init_signals(void)
{
	signal(SIGINT, reset_prompt);
}