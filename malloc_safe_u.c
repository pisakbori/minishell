/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_safe_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:21:33 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 19:30:10 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*m_ft_strdup(const char *s1)
{
	char	*res;

	if (!s1)
		return (NULL);
	res = ft_strdup(s1);
	if (!res)
		malloc_fail();
	return (res);
}

char	*m_ft_strjoin(char const *s1, char const *s2)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	if (!res)
		malloc_fail();
	return (res);
}

char	*m_ft_itoa(int n)
{
	char	*res;

	res = ft_itoa(n);
	if (!res)
		malloc_fail();
	return (res);
}

void	*m_ft_calloc(size_t count, size_t size)
{
	void	*res;

	res = ft_calloc(count, size);
	if (!res)
		malloc_fail();
	return (res);
}

int	m_dup2(int oldfd, int newfd)
{
	int	res;

	res = dup2(oldfd, newfd);
	if (res == -1)
	{
		ft_printf(2, "dup2 failed: %d\n", errno);
		set_exit_code(errno);
		free_and_exit(1);
	}
	return (res);
}
