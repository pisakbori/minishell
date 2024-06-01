/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:16:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/01 12:07:57 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ends_with_char(char *str, char c)
{
	return (str && *str && str[ft_strlen(str) - 1] == c);
}

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

int	str_equal(char *str1, char *str2)
{
	int	len1;
	int	len2;

	if (!str1 && !str2)
		return (1);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 != len2)
		return (0);
	return (!ft_strncmp(str1, str2, len1));
}

char	*found_variable(int name_len, char *line)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line_len == name_len)
		return (NULL);
	if (line[name_len] == '=')
		return (ft_strndup(line + name_len + 1, line_len - name_len));
	return (NULL);
}

char	*get_env_variable(char *var_name, char **env)
{
	int	i;
	int	name_len;

	i = -1;
	name_len = ft_strlen((const char *)var_name);
	while (env[++i])
	{
		if (!ft_strncmp(var_name, env[i], name_len))
			return (found_variable(name_len, env[i]));
	}
	return (NULL);
}

void	set_error(char *text, int err_code)
{
	// TODO: set last errorcode to err_code
	(void)err_code;
	ft_printf(2, "minishell: %s: ", text);
	perror(NULL);
}
