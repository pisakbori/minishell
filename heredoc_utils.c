/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:01:03 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/21 17:37:59 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*get_heredoc_path(int index)
{
	char	*heredoc_name;
	char	*temp;

	heredoc_name = ft_strdup("heredoc");
	temp = heredoc_name;
	heredoc_name = ft_strjoin(heredoc_name, ft_itoa(index));
	free(temp);
	temp = heredoc_name;
	heredoc_name = ft_path_join(state()->heredoc_dir, heredoc_name);
	free(temp);
	return (heredoc_name);
}

void	create_heredoc(int index, char *key1)
{
	char	*key;
	char	*hd_line;
	char	*heredoc_name;
	int		fd;

	hd_line = NULL;
	heredoc_name = get_heredoc_path(index);
	key = remove_chars(key1, "\"\'");
	fd = open(heredoc_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	signal(SIGINT, handle_heredoc_ctrl_c);
	while (1)
	{
		hd_line = readline("> ");
		if (!hd_line || str_equal(hd_line, key))
			break ;
		ft_printf(fd, expand_variables(hd_line, NULL));
		ft_printf(fd, "\n");
	}
	let_signals_through();
	close(fd);
	add_i_redir(index, DOUBLE, heredoc_name);
}
