/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:28:23 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/31 10:20:55 by bpisak-l         ###   ########.fr       */
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
