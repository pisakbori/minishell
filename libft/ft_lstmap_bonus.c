/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:20:10 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/03/13 11:39:53 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*fail(t_list **res, void (*del)(void *))
{
	ft_lstclear(res, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;
	void	*new_content;

	res = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
			return (fail(&res, del));
		new = ft_lstnew(new_content);
		if (!new)
		{
			free(new_content);
			fail(&res, del);
		}
		ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}
