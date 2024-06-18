/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:40:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/18 15:16:41 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(char *cmd)
{
	int	is_bltn;

	is_bltn = 0;
	is_bltn = str_equal(cmd, "exit");
	is_bltn = is_bltn || str_equal(cmd, "export");
	is_bltn = is_bltn || str_equal(cmd, "unset");
	is_bltn = is_bltn || str_equal(cmd, "env");
	is_bltn = is_bltn || str_equal(cmd, "echo");
	return (is_bltn);
}

int	exec_builtin(char **argv)
{
	t_exec	e;

	e = (t_exec){.argc = ft_arr_len(argv), .argv = argv};
	if (!ft_strlen(e.argv[0]))
		return (0);
	if (str_equal(e.argv[0], "exit"))
		on_exit_b(e);
	// if (str_equal(e.argv[0], "cd"))
	// 	on_cd(e);
	// if (str_equal(e.argv[0], "pwd"))
	// 	on_pwd(e);
	if (str_equal(e.argv[0], "env"))
		on_env(e);
	if (str_equal(e.argv[0], "export"))
		on_export(e);
	if (str_equal(e.argv[0], "echo"))
		on_echo(e);
	if (str_equal(e.argv[0], "unset"))
		on_unset(e);
	return (0);
}
