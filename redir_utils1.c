/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:49:03 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/01 15:24:20 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_filename(char *filename, int index)
{
	char	*fn;
	char	*temp;
	char	**parts;

	temp = expand_variables(filename, "\'\"");
	parts = str_split(temp, " \t", "\"\'");
	fn = remove_all_chars(temp, "\"\'");
	free(temp);
	replace_special_chars(fn);
	if (ft_arr_len(parts) > 1)
	{
		set_mini_error(filename, 1, "ambiguous redirect");
		state()->pipeline[index].redir.invalid = 1;
	}
	free_split_arr(parts);
	return (fn);
}

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

char	*get_arg_name(char *str)
{
	while (str_has("><", *str))
		str++;
	return (ft_strdup(str));
}
