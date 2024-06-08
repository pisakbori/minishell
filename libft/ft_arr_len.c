/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:35:32 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/08 13:21:42 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arr_len(char **arr)
{
	int	res;
	int	i;

	res = 0;
	i = -1;
	while (arr && arr[++i])
		res++;
	return (res);
}

int	ft_arr_3d_len(char ***arr)
{
	int	res;
	int	i;

	res = 0;
	i = -1;
	while (arr && arr[++i])
		res++;
	return (res);
}
