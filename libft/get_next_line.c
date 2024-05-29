/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:20:34 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/04/29 13:14:48 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_first_line_and_cache(char **result_str, char *eol, char **buff)
{
	char	*first_line;
	char	*remainder;
	int		initial_len;
	int		first_line_len;
	int		remainder_len;

	first_line_len = eol - *result_str + 1;
	initial_len = ft_strlen(*result_str);
	remainder_len = initial_len - first_line_len + 1;
	first_line = ft_calloc(first_line_len + 1, 1);
	if (!first_line)
		return (collect_garbage(result_str, buff));
	ft_strjoin_dupe(first_line, *result_str, first_line_len + 1);
	remainder = ft_calloc(remainder_len, 1);
	if (!remainder)
	{
		free(first_line);
		return (collect_garbage(result_str, buff));
	}
	ft_strjoin_dupe(remainder, eol + 1, remainder_len);
	collect_garbage(result_str, buff);
	*result_str = remainder;
	return (first_line);
}

char	*handle_eof(char **result_str, char **buff)
{
	char	*result;
	int		len;

	len = ft_strlen(*result_str);
	if (len)
	{
		result = ft_calloc(len + 1, 1);
		if (result)
			ft_strjoin_dupe(result, *result_str, len + 1);
	}
	else
		result = NULL;
	collect_garbage(result_str, buff);
	return (result);
}

void	*append_buff_to_res(int buff_len, char **res, char **buff, int *append)
{
	char	*final;
	int		res_len;

	res_len = ft_strlen(*res);
	append[0] += 1;
	if (append[0] == append[1])
	{
		append[1] *= 2;
		final = ft_calloc(BUFFER_SIZE * append[1] + 1, 1);
		if (!final)
			return (collect_garbage(res, buff));
		if (res_len)
		{
			ft_strjoin_dupe(final, *res, res_len + 1);
			ft_strjoin_dupe(final + res_len, *buff, buff_len + 1);
		}
		else
			ft_strjoin_dupe(final, *buff, buff_len + 1);
		free(*res);
		*res = final;
		return (final);
	}
	ft_strjoin_dupe(*res + res_len, *buff, buff_len + 1);
	return (*res);
}

void	*init(int fd, int *append)
{
	append[0] = 0;
	append[1] = 1;
	if (fd < 0)
		return (NULL);
	else
		return (append);
}

char	*get_next_line(int fd)
{
	char		*eol;
	int			read_len;
	static char	*result_str[4096];
	char		*buff;
	int			append[2];

	if (!init(fd, append))
		return (NULL);
	buff = ft_calloc(BUFFER_SIZE, 1);
	if (!buff)
		return (collect_garbage(&result_str[fd], &buff));
	eol = ft_strchr_dupe(result_str[fd], '\n');
	while (!eol)
	{
		read_len = read(fd, buff, BUFFER_SIZE);
		if (!read_len)
			return (handle_eof(&result_str[fd], &buff));
		else if (read_len == -1)
			return (collect_garbage(&result_str[fd], &buff));
		else if (append_buff_to_res(read_len, &result_str[fd], &buff, append))
			eol = ft_strchr_dupe(result_str[fd], '\n');
		else
			return (NULL);
	}
	return (get_first_line_and_cache(&result_str[fd], eol, &buff));
}
