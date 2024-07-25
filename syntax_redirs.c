/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:25:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 12:10:37 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	fail_on_unexpected_token(char *msg, char *token2, char *map)
{
	ft_memset(msg + 35, '`', 1);
	ft_strlcpy(msg + 36, token2, ft_strlen(token2) + 1);
	msg[ft_strlen(msg)] = '\'';
	set_error("minishell", 2, msg);
	free(map);
	return (0);
}

void	look_for_neighbor_token(char *str, int *i, char *token2)
{
	while (str[*i] && ft_is_space(str[*i]))
		*i = *i + 1;
	if (!str[*i])
		ft_strlcpy(token2, "newline", sizeof(token2));
	else if (str[*i] == '|')
		ft_strlcpy(token2, "|", sizeof(token2));
	else
		try_get_token(token2, str, i);
}

static int	valid_words(char *str, char *msg)
{
	int		i;
	char	token1[8];
	char	token2[8];
	char	*map;

	i = 0;
	if (!str || *str == 0)
		return (1);
	map = operation_map(str, NULL, "\'\"");
	while (map && str[i])
	{
		while (map[i + 1] && map[i] != KEEP)
			i++;
		try_get_token(token1, str, &i);
		if (token1[0])
		{
			look_for_neighbor_token(str, &i, token2);
			if (token2[0] != 0)
				return (fail_on_unexpected_token(msg, token2, map));
		}
		else
			i++;
	}
	free(map);
	return (1);
}

int	redirs_valid(char *str)
{
	int		res;
	char	msg[50];

	ft_memset(msg, 0, 50);
	ft_strlcpy(msg, "syntax error near unexpected token ", 50);
	res = 1;
	if (!valid_words(str, msg))
		res = 0;
	return (res);
}
