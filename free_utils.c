/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:20:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/14 13:15:28 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int i;

	if (!res)
		return ;
	i = -1;
	while (res[++i])
		free_split_arr(res[i]);
	free(res);
}