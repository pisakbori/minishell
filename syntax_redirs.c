/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:25:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/23 14:02:06 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	try_get_token(char *token, char *str, int *i)
{
	ft_memset(token, 0, 8);
	if (!str[*i])
		return ;
	if (str[*i] == '>')
	{
		token[0] = '>';
		*i = *i + 1;
		if (str[*i] == '>')
		{
			token[1] = '>';
			*i = *i + 1;
		}
	}
	else if (str[*i] == '<')
	{
		token[0] = '<';
		*i = *i + 1;
		if (str[*i] == '<')
		{
			token[1] = '<';
			*i = *i + 1;
		}
	}
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

static int	valid_words(char *str, char *msg)
{
	int		i;
	char	token1[8];
	char	token2[8];
	char	*map;

	i = 0;
	if (!str)
		return (1);
	map = operation_map(str, NULL, "\'\"");
	while (str[i])
	{
		while (map[i] != KEEP)
			i++;
		try_get_token(token1, str, &i);
		if (token1[0])
		{
			while (ft_isspace(str[i]))
				i++;
			if (!str[i])
				ft_strlcpy(token2, "newline", sizeof(token2));
			else if (str[i] == '|')
				ft_strlcpy(token2, "|", sizeof(token2));
			else
				try_get_token(token2, str, &i);
			if (token2[0] != 0)
			{
				ft_memset(msg + 35, '`', 1);
				ft_strlcpy(msg + 36, token2, ft_strlen(token2) + 1);
				msg[ft_strlen(msg)] = '\'';
				set_error("minishell", 2, msg);
				free(map);
				return (0);
			}
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
