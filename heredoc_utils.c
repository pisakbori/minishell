/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:01:03 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/29 11:11:16 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*get_heredoc_path(int index)
{
	char	*heredoc_name;
	char	*temp;
	char	*index_str;

	heredoc_name = m_ft_strdup("heredoc");
	temp = heredoc_name;
	index_str = m_ft_itoa(index);
	heredoc_name = m_ft_strjoin(temp, index_str);
	free(index_str);
	free(temp);
	return (heredoc_name);
}

static int	put_heredoc_line(char *hd_line, char *key, char *key1, int fd)
{
	char	*temp;

	if (str_equal(hd_line, key))
	{
		free(hd_line);
		return (0);
	}
	if (!hd_line)
		return (0);
	if (ft_strchr(key1, '\'') || ft_strchr(key1, '\"'))
		temp = m_ft_strdup(hd_line);
	else
		temp = expand_variables(hd_line, NULL);
	ft_printf(fd, temp);
	free(temp);
	ft_printf(fd, "\n");
	free(hd_line);
	return (1);
}

void	create_heredoc(int index, char *key1)
{
	char	*key;
	char	*hd_line;
	char	*heredoc_name;
	int		fd;

	if (!state()->heredocs_ok)
		return ;
	state()->n_heredocs = index;
	heredoc_name = get_heredoc_path(index);
	key = remove_chars(key1, "\"\'");
	fd = open(heredoc_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	signal(SIGINT, handle_heredoc_ctrl_c);
	while (1)
	{
		hd_line = read_debug("> ");
		if (!put_heredoc_line(hd_line, key, key1, fd))
			break ;
	}
	free(key);
	let_signals_through();
	close(fd);
	m_dup2(state()->backup_stdin, STDIN_FILENO);
	if (state()->heredocs_ok)
		add_i_redir(index, DOUBLE, heredoc_name);
	else
		free(heredoc_name);
}

void	remove_all_heredocs(int max_index)
{
	int		i;
	char	*heredoc_path;

	i = -1;
	while (++i <= max_index)
	{
		heredoc_path = get_heredoc_path(i);
		if (!access(heredoc_path, F_OK))
			unlink(heredoc_path);
		free(heredoc_path);
	}
}
