/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:41:46 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/29 12:28:13 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ./microshell /bin/ls 
// ./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
char	*get_cmd_path(char *bin_name, char **env)
{
	char *paths;
	char **path_arr;
	paths = get_env_variable("PATH", env);
	path_arr = ft_split(paths, ':');
	print_array(path_arr);
	return bin_name;
}


int main(int argc, char *argv[], char **env)
{
	char *cmd = "/bin/ls";
	if (argc >= 2)
		cmd = get_cmd_path(argv[1], env);
	execve(cmd, argv + 1, env);
	return 0;
}
