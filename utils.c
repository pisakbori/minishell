/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:16:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/29 12:34:16 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*ret;

	if (str == 0)
		return (0);
	ret = (char *)malloc(n + 1);
	if (ret == 0)
		return (0);
	i = -1;
	while (++i < n)
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}


char	*found_variable(int name_len, char *line)
{
	int		line_len;

	line_len = ft_strlen(line);
	if (line_len == name_len)
		return (NULL);
	if (line[name_len] == '=')
		return (ft_strndup(line + name_len + 1, line_len - name_len));
	return (NULL);
}

char	*get_env_variable(char *var_name, char **env)
{
	int		i;
	int		name_len;

	i = -1;
	name_len = ft_strlen((const char *)var_name);
	while (env[++i])
	{
		if (!ft_strncmp(var_name, env[i], name_len))
			return (found_variable(name_len, env[i]));
	}
	return (NULL);
}

void print_array(char **arr)
{
	int		i;
	i = -1;
	while (arr && arr[++i])
		printf("%s\n", arr[i]);
	
}