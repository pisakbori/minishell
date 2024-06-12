/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:25:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/12 20:10:09 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_valid_syntax(char *str)
{
	char *iter;

	iter = str;
	while (*iter)
	{
		if (*iter == '"')
			iter = ft_strchr(iter + 1, '"');
		else if (*iter == '\'')
			iter = ft_strchr(iter + 1, '\'');
		if (!iter)
		{
			set_exit_code(2);
			ft_printf(2, "Syntax error: Unterminated quoted string\n");
			return (0);
		}
		iter++;
	}
	return (1);
}