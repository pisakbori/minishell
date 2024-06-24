/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:18:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/24 15:42:05 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_exists(char *path)
{
	int	res;

	res = access(path, F_OK);
	return (!res);
}

int	is_exec(char *path)
{
	struct stat	sb;

	state()->cmd_path_status = IS_VALID;
	if (!strchr(path, '/'))
		state()->cmd_path_status = NOT_COMMAND;
	else if (access(path, F_OK))
		state()->cmd_path_status = INVALID_PATH;
	else if (is_dir(path))
		state()->cmd_path_status = IS_DIR;
	else if (!(stat(path, &sb) == 0 && sb.st_mode & S_IXUSR))
		state()->cmd_path_status = NO_EXEC_RIGHTS;
	return (state()->cmd_path_status == IS_VALID);
}

void	ft_path_join(char **path, char *bin_name)
{
	char	*temp;
	char	*full_path;

	if (!ends_with_char(*path, '/'))
	{
		temp = ft_strjoin(*path, "/");
		free(*path);
		*path = temp;
	}
	full_path = ft_strjoin(*path, bin_name);
	free(*path);
	*path = full_path;
}

void	set_path_error(char *path)
{
	t_path_status	status;

	status = state()->cmd_path_status;
	if (status == IS_DIR)
		set_error(path, 126, "Is a directory");
	else if (status == NO_EXEC_RIGHTS)
		set_error(path, 126, "Permission denied");
	else if (status == NOT_COMMAND)
		set_error(path, 127, "command not found");
	else if (status == INVALID_PATH)
		set_error(path, 127, " No such file or directory");
	if (status != IS_VALID)
		exit(state()->exit_code);
}

char	*get_cmd_path(char *bin_name)
{
	char	*paths;
	char	**p;
	int		i;
	char	*res;

	paths = get_env_variable("PATH");
	p = ft_split(paths, ':');
	ft_free((void **)&paths);
	i = -1;
	res = NULL;
	while (p[++i])
	{
		ft_path_join(&(p[i]), bin_name);
		if (is_exec(p[i]))
		{
			res = ft_strdup(p[i]);
			break ;
		}
	}
	free_split_arr(p);
	if (state()->cmd_path_status != IS_VALID && is_exec(bin_name))
		res = ft_strdup(bin_name);
	else
		set_path_error(bin_name);
	return (res);
}
