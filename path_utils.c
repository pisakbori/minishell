/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:18:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/24 11:03:38 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exec(char *path)
{
	struct stat	sb;

	state()->path_status = IS_VALID;
	if (access(path, F_OK))
		state()->path_status = NOT_EXIST;
	else if (is_dir(path))
		state()->path_status = IS_DIR;
	else if (!(stat(path, &sb) == 0 && sb.st_mode & S_IXUSR))
		state()->path_status = PERMISSION_DENIED;
	return (state()->path_status == IS_VALID);
}

char	*ft_path_join(char *path, char *bin_name)
{
	char	*temp;
	char	*full_path;

	if (!ends_with_char(path, '/') && (bin_name[0] != '/'))
	{
		temp = ft_strjoin(path, "/");
		full_path = ft_strjoin(temp, bin_name);
		free(temp);
	}
	else
		full_path = ft_strjoin(path, bin_name);
	return (full_path);
}

void	set_path_error(char *path)
{
	t_path_status	status;

	status = state()->path_status;
	if (status == IS_DIR)
		set_error(path, 126, "Is a directory");
	else if (status == PERMISSION_DENIED)
		set_error(path, 126, "Permission denied");
	else if (status == CMD_NOT_FOUND)
		set_error(path, 127, "command not found");
	else if (status == NOT_EXIST)
		set_error(path, 127, " No such file or directory");
	if (status != IS_VALID)
		exit(state()->exit_code);
}

char	*bin_using_path(char *paths, char *bin_name)
{
	char	**p;
	int		i;
	char	*path;
	char	*res;

	if (!paths)
		return (NULL);
	p = ft_split(paths, ':');
	res = NULL;
	i = -1;
	while (p && p[++i])
	{
		path = ft_path_join(p[i], bin_name);
		if (is_exec(path))
			res = path;
		else
			free(path);
	}
	free_split_arr(p);
	return (res);
}

// TODO: if path: check if executable/exists/isdir/permission
// if not path and no paths: CMD_NOT_FOUND
// if not path and paths, check for each $path/cmd if exists/executable
char	*get_cmd_path(char *bin_name)
{
	char	*paths;
	char	*res;
	char	*pth;

	paths = get_env_variable("PATH");
	res = NULL;
	if (str_equal(bin_name, "~"))
		pth = get_env_variable("HOME");
	else if (!paths && !ft_strchr(bin_name, '/'))
		pth = ft_strjoin("./", bin_name);
	else
		pth = ft_strdup(bin_name);
	if (ft_strchr(pth, '/'))
	{
		if (is_exec(pth))
			res = ft_strdup(pth);
		else
			set_path_error(pth);
	}
	else
	{
		res = bin_using_path(paths, bin_name);
		if (!res)
		{
			state()->path_status = CMD_NOT_FOUND;
			set_path_error(bin_name);
		}
	}
	free(paths);
	free(pth);
	return (res);
}
