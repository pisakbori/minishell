/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:25:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/27 20:02:31 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	valid_neighbors(char **words, char is_last_stage, char mute)
{
	int		i;
	char	error;
	char	msg[45];

	ft_strlcpy(msg, "syntax error near unexpected token ` '", 45);
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
			if (!mute)
				set_error("minishell", 2, msg);
			return (0);
		}
		if (is_bracket(words[i]))
		{
			if (!words[i + 1])
			{
				if (is_last_stage)
					ft_strlcpy(msg + 35, "`newline'", 10);
				else
					msg[36] = '|';
				if (!mute)
					set_error("minishell", 2, msg);
				return (0);
			}
			error += words[i + 1][0] == '>' || words[i + 1][0] == '<';
			if (error)
			{
				msg[36] = words[i + 1][0];
				if (!mute)
					set_error("minishell", 2, msg);
				return (0);
			}
		}
	}
	return (1);
}

int	has_valid_redirs(char *str, char mute)
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
		if (!valid_neighbors(words, stages[i + 1] == NULL, mute))
			res = 0;
		free_split_arr(words);
	}
	free_split_arr(stages);
	return (res);
}

int	quotes_valid(char *str, char mute)
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
			if (!mute)
				set_error("minishell", 2, msg);
			return (0);
		}
		str++;
	}
	return (1);
}

int	pipes_valid(char *str, char *eol_error, char *pipe_error, char mute)
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
			if (str[i] == '|' && !mute)
				set_error("minishell", 2, pipe_error);
			else if (!str[i] && !mute)
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
int	is_valid_syntax(char *str, char mute)
{
	char	eol_error[45];
	char	pipe_error[45];

	ft_strlcpy(eol_error, "syntax error near unexpected token `newline'", 45);
	ft_strlcpy(pipe_error, "syntax error near unexpected token `|'", 45);
	if (!quotes_valid(str, mute))
		return (0);
	if (!pipes_valid(str, eol_error, pipe_error, mute))
		return (0);
	if (!has_valid_redirs(str, mute))
		return (0);
	return (1);
}
