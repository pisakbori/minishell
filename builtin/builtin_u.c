/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:26:56 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 12:29:21 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_err_prompt(void)
{
	ft_printf(2, "minishell: ");
}

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

// A variable name must start with a character(A-Za-z) or an Underscore(_)
// then there can be any number of characters, digits(0-9) or underscore.
int	is_valid_name(char *name)
{
	if (!name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}
