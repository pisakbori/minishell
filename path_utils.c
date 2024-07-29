/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:18:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/29 14:53:26 by bpisak-l         ###   ########.fr       */
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

char	*path_as_cmd(char *paths, char *bin_name)
{
	char	*res;

	res = bin_using_path(paths, bin_name);
	if (!res)
	{
		state()->path_status = CMD_NOT_FOUND;
		set_path_error(bin_name);
	}
	return (res);
}

char	*handle_cmd_no_env(char *bin_name)
{
	char	*pth;
	char	*res;

	res = NULL;
	pth = ft_path_join("./", bin_name);
	if (is_exec(pth))
		res = m_ft_strdup(pth);
	else
		set_path_error(bin_name);
	free(pth);
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
	if (!paths && !strchr(bin_name, '/'))
		return (handle_cmd_no_env(bin_name));
	res = NULL;
	pth = NULL;
	if (str_equal(bin_name, "~"))
		pth = get_env_variable("HOME");
	else
		pth = m_ft_strdup(bin_name);
	if (ft_strchr(pth, '/'))
	{
		if (is_exec(pth))
			res = m_ft_strdup(pth);
		else
			set_path_error(pth);
	}
	else
		res = path_as_cmd(paths, bin_name);
	free(paths);
	free(pth);
	return (res);
}
