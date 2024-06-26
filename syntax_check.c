/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:25:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/26 11:39:39 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	valid_neighbors(char **words)
{
	int		i;
	char	error;
	char	msg[39];

	ft_strlcpy(msg, "syntax error near unexpected token ' '", 39);
	i = -1;
	error = 0;
	while (words && words[++i])
	{
		error += starts_with(words[i], ">>>");
		error += starts_with(words[i], "><");
		error += starts_with(words[i], ">><");
		if (error)
		{
			msg[36] = '>';
			set_error("minishell", 2, msg);
			return (0);
		}
		error += starts_with(words[i], "<<<");
		error += starts_with(words[i], "<>");
		error += starts_with(words[i], "<<>");
		if (error)
		{
			msg[36] = '<';
			set_error("minishell", 2, msg);
			return (0);
		}
		if (is_bracket(words[i]))
		{
			if (!words[i + 1])
			{
				msg[36] = '|';
				set_error("minishell", 2, msg);
				return (0);
			}
			error += words[i + 1][0] == '>' || words[i + 1][0] == '<';
			if (error)
			{
				msg[36] = words[i + 1][0];
				set_error("minishell", 2, msg);
				return (0);
			}
		}
	}
	return (1);
}

int	has_valid_redirs(char *str)
{
	char	**stages;
	char	**words;
	int		i;
	int		res;

	i = -1;
	res = 1;
	stages = str_split(str, "|", "\"\'");
	while (stages[++i])
	{
		words = str_split(stages[i], " \t", "\"\'");
		if (!valid_neighbors(words))
			res = 0;
		free_split_arr(words);
	}
	free_split_arr(stages);
	return (res);
}

// TODO:check for > empty, or > |
int	syntax_check(char *str)
{
	char	msg[42];
	char	*start;

	start = str;
	ft_strlcpy(msg, "Syntax error: Unterminated quoted string\n", 42);
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
	if (!has_valid_redirs(start))
		return (0);
	return (1);
}
