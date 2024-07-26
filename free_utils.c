/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:20:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/26 14:49:15 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_fail_free(char **res, int i, char *map, char *clone)
{
	free(clone);
	free(map);
	while (i >= 0)
	{
		free(*(res + i));
		i--;
	}
	free(res);
	malloc_fail();
	return (NULL);
}

void	free_split_arr(char **res)
{
	int	i;

	if (!res)
		return ;
	i = -1;
	while (res[++i])
	{
		free(res[i]);
		res[i] = NULL;
	}
	free(res);
	res = NULL;
}

void	free_redirs(void)
{
	int		i;
	int		len;
	t_redir	*redirs;

	i = -1;
	redirs = state()->redirs;
	if (!redirs)
		return ;
	len = pipeline_len(state()->pipeline);
	while (++i < len)
	{
		if (redirs[i].in)
			free(redirs[i].in);
		if (redirs[i].out)
			free(redirs[i].out);
	}
	free(state()->redirs);
	state()->redirs = NULL;
}

void	free_pipeline(void)
{
	int	i;

	i = 0;
	free_redirs();
	if (state()->pipes)
	{
		free(state()->pipes);
		state()->pipes = NULL;
	}
	if (!state()->pipeline)
		return ;
	while (state()->pipeline[i].argv != NULL)
	{
		free(state()->pipeline[i].redir.in);
		free(state()->pipeline[i].redir.out);
		if (state()->pipeline[i].argv)
			free_split_arr(state()->pipeline[i].argv);
		state()->pipeline[i].argv = NULL;
		i++;
	}
	free(state()->pipeline);
	state()->pipeline = NULL;
}

void	free_and_exit(int mute)
{
	t_state	*s;
	int		exit_code;

	s = state();
	exit_code = s->exit_code;
	if (s->cwd)
		free(s->cwd);
	if (s->oldcwd)
		free(s->oldcwd);
	if (s->last_arg)
		free(s->last_arg);
	free_pipeline();
	free_split_arr(s->env);
	free(s->home_backup);
	free(s);
	clear_history();
	rl_replace_line("", 1);
	if (!mute)
		ft_printf(1, "exit\n");
	exit(exit_code);
}
