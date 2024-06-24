/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:49:03 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/24 14:26:30 by bpisak-l         ###   ########.fr       */
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
	int	err;

	if (!str || !str[0] || !str[1])
		return (0);
	res = 1;
	res = res && str_has("><", str[0]);
	err = res && (str[0] != str[1] && str_has("><", str[1]));
	err = err || (str_has("><", str[1]) && str_has("><", str[2]));
	if (err)
		set_error("minishell", 2, "syntax error near unexpected token\n");
	res = res && (str[0] == str[1] || !str_has("><", str[1]));
	return (res);
}

int	is_separated_redir(char *symbol, char *arg)
{
	int	err;

	err = 0;
	err = err || (is_bracket(symbol) && !arg);
	err = err || (is_bracket(symbol) && is_unsplit_redir(arg));
	err = err || (is_bracket(symbol) && is_bracket(arg));
	if (err)
		set_error("minishell", 2, "syntax error near unexpected token\n");
	return (is_bracket(symbol) && is_redir_arg(arg));
}

char	*get_arg_name(char *str)
{
	while (str_has("><", *str))
		str++;
	return (ft_strdup(str));
}
