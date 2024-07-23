/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:07:58 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/23 13:16:12 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_valid(char *str)
{
	char	msg[42];

	ft_strlcpy(msg, "Syntax error: Unterminated quoted string", 41);
	while (*str)
	{
		if (*str == '"')
			str = ft_strchr(str + 1, '"');
		else if (*str == '\'')
			str = ft_strchr(str + 1, '\'');
		if (!str)
		{
			set_error("minishell", 2, msg);
			return (0);
		}
		str++;
	}
	return (1);
}

int	is_valid_syntax(char *str)
{
	char	eol_error[45];
	char	pipe_error[45];

	ft_strlcpy(eol_error, "syntax error near unexpected token `newline'", 45);
	ft_strlcpy(pipe_error, "syntax error near unexpected token `|'", 45);
	if (!quotes_valid(str))
		return (0);
	if (!pipes_valid(str, eol_error, pipe_error))
		return (0);
	if (!redirs_valid(str))
		return (0);
	return (1);
}
