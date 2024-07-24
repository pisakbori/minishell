/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:23:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/24 15:42:26 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**keep_marked_only(char *map, char **parts)
{
	int		len;
	char	**res;
	int		j;
	int		i;

	len = char_freq(map, KEEP);
	res = ft_calloc(len + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (map[++i])
	{
		if (map[i] == KEEP)
			res[j++] = ft_strdup(parts[i]);
	}
	return (res);
}
