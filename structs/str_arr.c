/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:28:23 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/31 21:07:24 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_arr.h"

void	print(t_str_arr *self)
{
	int	i;

	i = -1;
	while (self->arr && self->arr[++i])
		printf("%s\n", self->arr[i]);
}

int	first_index(char **arr, char *delim)
{
	int	res;
	int	i;

	res = -1;
	i = 0;
	while (arr && arr[i] && !ft_strncmp(arr[i], delim, ft_strlen(arr[i])))
	{
		res = i;
		i++;
	}
	return (res);
}

char	**clone_until(char **arr, char *delim)
{
	int		i;
	int		size;
	char	**new;

	if (!delim)
		size = ft_arr_len(arr);
	else
		size = first_index(arr, delim);
	i = -1;
	new = ft_calloc(size + 1, sizeof(char *));
	if (!new)
		exit(EXIT_FAILURE);
	while (arr && arr[++i] && i < size)
		new[i] = ft_strdup(arr[i]);
	return (new);
}

void	delete_str_arr(t_str_arr *p)
{
	int	i;

	i = -1;
	while (p->arr[++i])
	{
		ft_free((void **)&p->arr[i]);
	}
	ft_free((void **)&p->arr);
	free(p);
}

t_str_arr	*new_str_arr(char **arr)
{
	t_str_arr	*p;

	p = (t_str_arr *)malloc(sizeof(t_str_arr));
	if (!p)
		return (NULL);
	p->arr = arr;
	p->print = print;
	p->delete = delete_str_arr;
	return (p);
}
