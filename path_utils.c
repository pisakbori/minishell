/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:18:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/26 16:00:33 by bpisak-l         ###   ########.fr       */
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

	state()->path_status = IS_VALID;
	if (!strchr(path, '/'))
		state()->path_status = NOT_COMMAND;
	else if (access(path, F_OK))
		state()->path_status = NOT_EXIST;
	else if (is_dir(path))
		state()->path_status = IS_DIR;
	else if (!(stat(path, &sb) == 0 && sb.st_mode & S_IXUSR))
		state()->path_status = PERMISSION_DENIED;
	return (state()->path_status == IS_VALID);
}

int	is_redirectable(char *path, t_path_status correct_status)
{
	struct stat	sb;
	int			exists;

	state()->path_status = IS_VALID;
	exists = 1;
	if (access(path, F_OK))
	{
		state()->path_status = NOT_EXIST;
		exists = 0;
	}
	// else if (is_dir(path))
	// 	state()->path_status = IS_DIR;
	if (exists && (stat(path, &sb) == 0 && sb.st_mode & S_IWUSR))
		state()->path_status = WRITE_RIGHTS;
	if (exists && (stat(path, &sb) == 0 && sb.st_mode & S_IRUSR))
		state()->path_status = READ_RIGHTS;
	return (state()->path_status == correct_status);
}

char	*ft_path_join(char *path, char *bin_name)
{
	char	*temp;
	char	*full_path;

	if (!ends_with_char(path, '/'))
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
	else if (status == NOT_COMMAND)
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

	p = ft_split(paths, ':');
	ft_free((void **)&paths);
	res = NULL;
	i = -1;
	while (p[++i])
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

char	*get_cmd_path(char *bin_name)
{
	char	*paths;
	char	*res;

	paths = get_env_variable("PATH");
	if (!paths)
		paths = state()->backup_path;
	res = bin_using_path(paths, bin_name);
	if (state()->path_status != IS_VALID && is_exec(bin_name))
		res = ft_strdup(bin_name);
	else if (!res)
		set_path_error(bin_name);
	return (res);
}
