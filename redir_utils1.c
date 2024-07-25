/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:49:03 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 12:10:43 by bpisak-l         ###   ########.fr       */
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
	fn = remove_chars(temp, "\"\'");
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

void	try_get_token(char *token, char *str, int *i)
{
	ft_memset(token, 0, 8);
	if (!str || !str[*i])
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
