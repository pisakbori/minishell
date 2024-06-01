/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:18:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/01 12:44:06 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	path_exists(char *path)
{
	int	res;

	res = access(path, F_OK);
	return (!res);
}

int	is_exec(char *path)
{
	int	res;

	if (!path_exists(path))
		return (0);
	res = access(path, X_OK);
	return (!res);
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

char	*get_cmd_path(char *bin_name, char **env)
{
	char *paths;
	t_str_arr *p;
	int i;
	char *res;

	paths = get_env_variable("PATH", env);
	p = new_str_arr(ft_split(paths, ':'));
	ft_free((void **)&paths);
	i = -1;
	res = NULL;
	if (!path_exists(bin_name))
	{
		while (p->arr[++i])
		{
			ft_path_join(&(p->arr[i]), bin_name);
			if (is_exec(p->arr[i]))
				res = ft_strdup(p->arr[i]);
		}
	}
	else if (is_exec(bin_name))
		res = ft_strdup(bin_name);
	if (!res)
		set_error(bin_name, errno);
	p->delete (p);
	return (res);
}