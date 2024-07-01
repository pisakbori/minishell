/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:07:58 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/01 15:10:38 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
