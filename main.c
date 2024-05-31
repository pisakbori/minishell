/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:41:46 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/31 20:06:31 by bpisak-l         ###   ########.fr       */
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
	char		*res;

	paths = get_env_variable("PATH", env);
	p = new_str_arr(ft_split(paths, ':'));
	ft_free((void **)&paths);
	i = -1;
	res = NULL;
	if (starts_with(bin_name, "./"))
	{
		if (is_exec(bin_name))
			res = ft_strdup(bin_name);
	}
	else
	{
		while (p->arr[++i])
		{
			ft_path_join(&(p->arr[i]), bin_name);
			if (is_exec(p->arr[i]))
				res = ft_strdup(p->arr[i]);
		}
	}
	if (!res)
		set_error(bin_name, errno);
	p->delete (p);
	return (res);
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
