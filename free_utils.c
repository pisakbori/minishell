/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:20:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/21 15:05:55 by bpisak-l         ###   ########.fr       */
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

void	free_2d_split_arr(char ***res)
{
	int	i;

	if (!res)
		return ;
	i = -1;
	while (res[++i])
		free_split_arr(res[i]);
	free(res);
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
	free_split_arr(s->env);
	free(s);
	ft_printf(1, "exit\n");
	exit(exit_code);
}
