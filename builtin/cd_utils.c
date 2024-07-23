/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:25:58 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/23 17:53:09 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_dir(char *path)
{
	struct stat	buf;

	stat(path, &buf);
	return (S_ISDIR(buf.st_mode));
}

int	is_valid_path(char *path)
{
	int			y;
	struct stat	buf;

	y = stat(path, &buf);
	if (y)
	{
		print_err_prompt();
		ft_printf(2, "cd: %s: No such file or directory\n", path);
	}
	else if (!is_dir(path))
	{
		print_err_prompt();
		ft_printf(2, "cd: %s: Not a directory\n", path);
	}
	else if (access(path, X_OK) != 0)
	{
		print_err_prompt();
		ft_printf(2, "cd: %s: Permission denied\n", path);
	}
	else
		return (1);
	set_exit_code(1);
	return (0);
}
