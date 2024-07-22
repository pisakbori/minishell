/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:25:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/18 16:33:07 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	valid_wordstart(char **words, char *msg)
{
	int		i;
	char	error;

	i = -1;
	while (words[++i])
	{
		error = starts_with(words[i], ">>>");
		error += starts_with(words[i], "><") + starts_with(words[i], ">><");
		if (error)
			msg[36] = '>';
		else
		{
			error += starts_with(words[i], "<<<") + starts_with(words[i], "<>");
			error += starts_with(words[i], "<<>");
			if (error)
				msg[36] = '<';
		}
		if (error)
		{
			set_error("minishell", 2, msg);
			return (0);
		}
	}
	return (1);
}

static int	valid_neighbors(char **words, char is_last_stage, char *msg)
{
	int	i;

	i = -1;
	while (words && words[++i] && is_bracket(words[i]))
	{
		if (!words[i + 1])
		{
			if (is_last_stage)
				ft_strlcpy(msg + 35, "`newline'", 10);
			else
				msg[36] = '|';
			set_error("minishell", 2, msg);
			return (0);
		}
		else if (words[i + 1][0] == '>' || words[i + 1][0] == '<')
		{
			msg[36] = words[i + 1][0];
			set_error("minishell", 2, msg);
			return (0);
		}
	}
	return (1);
}

int	redirs_valid(char *str)
{
	char	**stages;
	char	**words;
	int		i;
	int		res;
	char	msg[45];

	ft_strlcpy(msg, "syntax error near unexpected token ` '", 45);
	i = -1;
	res = 1;
	stages = str_split(str, "|", "\"\'");
	while (stages[++i])
	{
		words = str_split(stages[i], " \t", "\"\'");
		if (!valid_wordstart(words, msg))
			res = 0;
		else if (!valid_neighbors(words, stages[i + 1] == NULL, msg))
			res = 0;
		free_split_arr(words);
	}
	free_split_arr(stages);
	return (res);
}

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
