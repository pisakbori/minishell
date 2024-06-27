/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:20:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/27 15:26:35 by bpisak-l         ###   ########.fr       */
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
	return (NULL);
}

void	free_split_arr(char **res)
{
	int	i;

	i = -1;
	while (res && res[++i])
		free(res[i]);
	free(res);
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
		if (state()->pipeline[i].argv)
			free_split_arr(state()->pipeline[i].argv);
		state()->pipeline[i].argv = NULL;
		i++;
	}
	free(state()->pipeline);
	state()->pipeline = NULL;
}

void	free_and_exit(void)
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
	free(s);
	ft_printf(1, "exit\n");
	exit(exit_code);
}
