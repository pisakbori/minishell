/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:01:03 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/23 13:58:35 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*get_heredoc_path(int index)
{
	char	*heredoc_name;
	char	*temp;
	char	*index_str;

	heredoc_name = ft_strdup("heredoc");
	temp = heredoc_name;
	index_str = ft_itoa(index);
	heredoc_name = ft_strjoin(temp, index_str);
	free(index_str);
	free(temp);
	return (heredoc_name);
}

void	create_heredoc(int index, char *key1)
{
	char	*key;
	char	*hd_line;
	char	*heredoc_name;
	char	*temp;
	int		fd;

	state()->n_heredocs++;
	hd_line = NULL;
	heredoc_name = get_heredoc_path(index);
	key = remove_chars(key1, "\"\'");
	fd = open(heredoc_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	signal(SIGINT, handle_heredoc_ctrl_c);
	while (1)
	{
		if (isatty(fileno(stdin)))
			hd_line = readline("> ");
		else
		{
			hd_line = get_next_line(fileno(stdin));
			hd_line = ft_strtrim(hd_line, "\n");
		}
		if (str_equal(hd_line, key))
		{
			free(hd_line);
			break ;
		}
		if (!hd_line)
			break ;
		if (ft_strchr(key1, '\'') || ft_strchr(key1, '\"'))
			temp = ft_strdup(hd_line);
		else
			temp = expand_variables(hd_line,
									NULL);
		ft_printf(fd, temp);
		free(temp);
		ft_printf(fd, "\n");
		free(hd_line);
	}
	free(key);
	let_signals_through();
	close(fd);
	add_i_redir(index, DOUBLE, heredoc_name);
}

void	remove_all_heredocs(int max_index)
{
	int		i;
	char	*heredoc_path;

	i = -1;
	while (++i < max_index)
	{
		heredoc_path = get_heredoc_path(i);
		if (access(heredoc_path, F_OK))
		{
			free(heredoc_path);
			return ;
		}
		unlink(heredoc_path);
		free(heredoc_path);
	}
}
