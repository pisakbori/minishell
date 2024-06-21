/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:25:58 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/21 15:53:10 by bpisak-l         ###   ########.fr       */
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
		print_prompt();
		ft_printf(2, "cd: %s: No such file or directory\n", path);
		set_exit_code(1);
		return (0);
	}
	else if (!is_dir(path))
	{
		print_prompt();
		ft_printf(2, "cd: %s: Not a directory\n", path);
		set_exit_code(1);
		return (0);
	}
	else
		return (1);
}
