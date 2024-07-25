/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:19:24 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 12:20:12 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_code(int ext)
{
	if (WIFSIGNALED(ext))
		return (128 + WTERMSIG(ext));
	else if (WIFEXITED(ext))
		return (WEXITSTATUS(ext));
	else
		return (ext);
}

void	set_path_error(char *path)
{
	t_path_status	status;

	status = state()->path_status;
	if (status == IS_DIR)
		set_error(path, 126, "Is a directory");
	else if (status == PERMISSION_DENIED)
		set_error(path, 126, "Permission denied");
	else if (status == CMD_NOT_FOUND)
		set_error(path, 127, "command not found");
	else if (status == NOT_EXIST)
		set_error(path, 127, " No such file or directory");
	if (status != IS_VALID)
		exit(state()->exit_code);
}
