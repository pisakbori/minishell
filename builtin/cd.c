/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:00 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/24 21:30:09 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	navigate_to_path(char *path)
{
	char	cwd[4096];

	chdir(path);
	getcwd(cwd, 4096);
	set_cwd(cwd);
	set_exit_code(0);
}

void	navigate_to_oldpwd(void)
{
	char	*dest_path;

	dest_path = get_env_variable("OLDPWD");
	if (!dest_path)
		set_mini_error("cd", 1, "OLDPWD not set");
	else
	{
		ft_printf(1, "%s\n", dest_path);
		navigate_to_path(dest_path);
	}
	free(dest_path);
}

void	navigate(char *dest_path)
{
	if (is_valid_path(dest_path))
		navigate_to_path(dest_path);
}

int	should_i_go_home(t_exec e)
{
	int	a_h;

	a_h = 0;
	a_h = e.argc == 2;
	a_h = a_h && (str_equal(e.argv[1], "~") || str_equal(e.argv[1], "--"));
	a_h = a_h || e.argc == 1;
	return (a_h);
}

void	on_cd(t_exec e)
{
	char	*home;

	if (e.argc > 2)
	{
		set_mini_error("cd", 1, "too many arguments");
		return ;
	}
	home = get_env_variable("HOME");
	if (should_i_go_home(e))
	{
		if (home)
			navigate(home);
		else
		{
			set_mini_error("cd", 1, "HOME not set");
			return ;
		}
	}
	else if (str_equal(e.argv[1], "-"))
		navigate_to_oldpwd();
	else
		navigate(e.argv[1]);
	free(home);
}
