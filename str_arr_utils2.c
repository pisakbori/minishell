/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:53:13 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/26 14:19:38 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*str_join_all(char **arr, char *sepa)
{
	int		i;
	char	*res;
	char	*temp;

	res = ft_strdup("");
	i = -1;
	while (arr[++i])
	{
		temp = res;
		res = ft_strjoin(res, arr[i]);
		free(temp);
		if (arr[i + 1])
		{
			temp = res;
			res = ft_strjoin(res, sepa);
			free(temp);
		}
	}
	return (res);
}
