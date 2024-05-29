/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:26:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/31 10:20:03 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_ARR_H
# define STR_ARR_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_str_arr
{
	char	**arr;
	void	(*print)(struct s_str_arr *self);
	void	(*delete)(struct s_str_arr *self);
}			t_str_arr;

t_str_arr	*new_str_arr(char **arr);

#endif