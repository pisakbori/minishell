/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:41:46 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/31 17:12:21 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ./microshell /bin/ls
// ./microshell /bin/ls "|" /usr/bin/grep microshell ";"
//	/bin/echo i love my microshell
char	*get_cmd_path(char *bin_name, char **env)
{
	char		*paths;
	t_str_arr	*p;
	int			i;
	int			is_executable;

	paths = get_env_variable("PATH", env);
	p = new_str_arr(ft_split(paths, ':'));
	ft_free((void **)&paths);
	i = -1;
	is_executable = 0;
	if (path_exists(bin_name) && path_is_executable(bin_name))
		is_executable = 1;
	else
	{
		while (p->arr[++i])
		{
			ft_path_join(&(p->arr[i]), bin_name);
			if (path_exists(p->arr[i]))
				if (path_is_executable(p->arr[i]))
					is_executable = 1;
		}
	}
	if (!is_executable)
		set_error(bin_name, errno);
	// p->print(p);
	p->delete (p);
	return (bin_name);
}

int	main(int argc, char *argv[], char **env)
{
	char	*cmd;

	cmd = "/bin/ls";
	if (argc >= 2)
		cmd = get_cmd_path(argv[1], env);
	execve(cmd, argv + 1, env);
	return (0);
}
