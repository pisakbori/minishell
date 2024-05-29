/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:57:36 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/23 13:21:49 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_point
{
	int		x;
	int		y;

	// Function pointers for methods
	void	(*setX)(t_point *self, int x);
	void	(*setY)(t_point *self, int y);
	int		(*getX)(t_point *self);
	int		(*getY)(t_point *self);
	void	(*print)(t_point *self);
}			t_point;
