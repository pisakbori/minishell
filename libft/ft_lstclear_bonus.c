/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:21:10 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/12 17:19:31 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*iter;
	t_list	*temp;

	if (!lst || !(*lst))
		return ;
	iter = *lst;
	while (iter)
	{
		temp = iter->next;
		ft_lstdelone(iter, del);
		iter = temp;
	}
	*lst = NULL;
}
