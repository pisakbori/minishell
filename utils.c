/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:16:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/12 22:05:23 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_array(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		printf("%s\n", arr[i]);
}

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

void	set_error(char *text, int err_code)
{
	// TODO: set last errorcode to err_code
	(void)err_code;
	ft_printf(2, "%s: ", text);
	perror(NULL);
}

int	starts_with(char *str, char *start)
{
	return (!ft_strncmp(str, start, ft_strlen(start)));
}

void	swap(char *s1, char *s2)
{
	char	*temp;

	temp = s1;
	s1 = s2;
	s2 = temp;
}

void	ft_sort_alph(char **arr)
{
	int	i;
	int	len;
	int	j;

	i = -1;
	len = ft_arr_len(arr);
	while (++i < len - 1)
	{
		j = 0;
		while (j < i - 1)
		{
			if (ft_strncmp(arr[j], arr[j + 1], ft_strlen(arr[i]) + 1) > 0)
				swap(arr[j], arr[j + 1]);
			j++;
		}
	}
}
