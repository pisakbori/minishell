/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:41:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/26 13:53:28 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**clone_str_arr(char **arr)
{
	int		i;
	int		size;
	char	**new;

	size = ft_arr_len(arr);
	i = -1;
	new = ft_calloc(size + 1, sizeof(char *));
	if (!new)
		exit(EXIT_FAILURE);
	while (arr && arr[++i])
	{
		new[i] = ft_strdup(arr[i]);
	}
	return (new);
}

char	**append_to_str_arr(char **arr, char *str)
{
	int		i;
	int		size;
	char	**new;

	size = ft_arr_len(arr) + 1;
	new = ft_calloc(size + 1, sizeof(char *));
	if (!new)
		exit(EXIT_FAILURE);
	i = 0;
	while (arr && arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	free_split_arr(arr);
	new[i] = ft_strdup(str);
	return (new);
}

void	print_array(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		ft_printf(1, "%s\n", arr[i]);
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
