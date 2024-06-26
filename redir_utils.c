/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:49:03 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/26 13:50:53 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_bracket(char *str)
{
	int	res;

	if (!str)
		return (0);
	res = 0;
	res = res || str_equal(str, ">");
	res = res || str_equal(str, ">>");
	res = res || str_equal(str, "<");
	res = res || str_equal(str, "<<");
	return (res);
}

int	is_redir_arg(char *str)
{
	int	res;

	if (!str || !*str)
		return (0);
	res = 1;
	res = res && !starts_with(str, ">");
	res = res && !starts_with(str, "<");
	return (res);
}

int	is_unsplit_redir(char *str)
{
	int	res;

	res = starts_with(str, ">>");
	res += starts_with(str, "<");
	res += starts_with(str, ">");
	res *= !starts_with(str, "<<");
	return (res);
}

int	is_separated_heredoc(char *symbol, char *arg)
{
	return (str_equal(symbol, "<<") && is_redir_arg(arg));
}

char	*get_arg_name(char *str)
{
	while (str_has("><", *str))
		str++;
	return (ft_strdup(str));
}
