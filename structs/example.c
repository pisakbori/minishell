/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:52:40 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/23 13:23:14 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "example.h"

void	setX(t_point *self, int x)
{
	self->x = x;
}

void	setY(t_point *self, int y)
{
	self->y = y;
}

int	getX(t_point *self)
{
	return (self->x);
}

int	getY(t_point *self)
{
	return (self->y);
}

void	print(t_point *self)
{
	printf("t_point(%d, %d)\n", self->x, self->y);
}

t_point	*new_point(int x, int y)
{
	t_point	*p;

	p = (t_point *)malloc(sizeof(t_point));
	if (!p)
		return (NULL);
	p->x = x;
	p->y = y;
	p->setX = setX;
	p->setY = setY;
	p->getX = getX;
	p->getY = getY;
	p->print = print;
	return (p);
}

void	delete_point(t_point *p)
{
	free(p);
}

int	main(void)
{
	t_point	*p1;

	p1 = new_point(10, 20);
	if (!p1)
	{
		fprintf(stderr, "Failed to allocate memory for t_point\n");
		return (1);
	}
	p1->print(p1);
	p1->setX(p1, 30);
	p1->setY(p1, 40);
	printf("X: %d, Y: %d\n", p1->getX(p1), p1->getY(p1));
	p1->print(p1);
	delete_point(p1);
	return (0);
}
