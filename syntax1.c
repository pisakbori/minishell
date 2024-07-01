/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:25:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/01 15:10:08 by bpisak-l         ###   ########.fr       */
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
	return (1);
}

int	pipes_valid(char *str, char *eol_error, char *pipe_error)
{
	char	*map;
	int		i;

	map = operation_map(str, " \t", "\"\'");
	i = -1;
	while (map[++i])
	{
		if (map[i] == KEEP && str[i] == '|')
		{
			i++;
			while (map[i] == DELIMITER)
				i++;
			if (str[i] == '|')
				set_error("minishell", 2, pipe_error);
			else if (!str[i])
				set_error("minishell", 2, eol_error);
			if (str[i] == '|' || !str[i])
			{
				free(map);
				return (0);
			}
		}
	}
	free(map);
	return (1);
}

// TODO:check for ||
