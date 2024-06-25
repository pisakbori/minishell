/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:18:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/25 14:21:48 by bpisak-l         ###   ########.fr       */
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

char	*get_cmd_path(char *bin_name)
{
	char	*paths;
	char	**p;
	int		i;
	char	*res;

	paths = get_env_variable("PATH");
	if (!paths)
		paths = state()->backup_path;
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
	if (state()->path_status != IS_VALID && is_exec(bin_name))
		res = ft_strdup(bin_name);
	else
		set_path_error(bin_name);
	return (res);
}
