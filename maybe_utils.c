/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maybe_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:16:20 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/10 16:18:04 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maybe_utils.h"
#include "minishell.h"

t_env_var	*get_name_value(char *env_line)
{
	char		*eq;
	int			eq_index;
	t_env_var	*res;

	eq = ft_strchr(env_line, '=');
	res = ft_calloc(1, sizeof(t_env_var));
	if (!eq)
	{
		res->name = ft_strdup(env_line);
		res->value = ft_strdup("");
	}
	else
	{
		eq_index = eq - env_line;
		res->name = sndup(env_line, eq_index);
		res->value = sndup(eq + 1, ft_strlen(env_line) - eq_index - 1);
	}
	return (res);
}

int	starts_with(char *str, char *start)
{
	return (!ft_strncmp(str, start, ft_strlen(start)));
}
