/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:00 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/25 15:05:02 by bpisak-l         ###   ########.fr       */
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
	if (!dest_path[0])
		set_mini_error("cd", 1, "OLDPWD not set");
	else
		ft_printf(1, "%s\n", dest_path);
	free(dest_path);
}

void	navigate(char *dest_path)
{
	if (is_valid_path(dest_path))
		navigate_to_path(dest_path);
	free(dest_path);
}

void	navigate_relative_home(char *path, char *home)
{
	char	*dest_path;

	dest_path = ft_strdup(home);
	if (ft_strlen(path) > 1)
	{
		free(dest_path);
		dest_path = ft_strjoin(home, path + 1);
	}
	navigate(dest_path);
}

void	on_cd(t_exec e)
{
	char	*dest_path;
	char	*home;

	if (e.argc > 2)
	{
		set_mini_error("cd", 1, "too many arguments");
		return ;
	}
	home = get_env_variable("HOME");
	dest_path = NULL;
	if (e.argc == 1 && home)
		dest_path = ft_strdup(home);
	else if (e.argc == 1 && !home)
	{
		set_mini_error("cd", 1, "HOME not set");
		return ;
	}
	else if (e.argv[1][0] == '~')
		navigate_relative_home(e.argv[1], home);
	else if (e.argv[1][0] == SKIP && ft_strlen(e.argv[1]) == 1)
		return (navigate_to_oldpwd());
	else
		dest_path = ft_strdup(e.argv[1]);
	navigate(dest_path);
	free(home);
}
