/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:30:41 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/18 16:37:59 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	starts_with_pipe(char *str, char *map, char *pipe_error)
{
	int	i;

	i = 0;
	while (map[i] == DELIMITER)
		i++;
	if (str[i] == '|')
	{
		free(map);
		set_error("minishell", 2, pipe_error);
		return (1);
	}
	return (0);
}

void	set_syntax_error(char *str, int i, char *eol_error, char *pipe_error)
{
	if (str[i] == '|')
		set_error("minishell", 2, pipe_error);
	else if (!str[i])
		set_error("minishell", 2, eol_error);
}

int	pipes_valid(char *str, char *eol_error, char *pipe_error)
{
	char	*map;
	int		i;

	map = operation_map(str, " \t", "\"\'");
	if (starts_with_pipe(str, map, pipe_error))
		return (0);
	i = -1;
	while (map[++i])
	{
		if (map[i] == KEEP && str[i] == '|')
		{
			i++;
			while (map[i] == DELIMITER)
				i++;
			set_syntax_error(str, i, eol_error, pipe_error);
			if (str[i] == '|' || !str[i])
			{
				free(map);
				return (0);
			}
		}
	}
	free(map);
	return (1);
}

// TODO:check for ||
