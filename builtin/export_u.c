/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:15:43 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 12:19:13 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	set_plus_and_eq_ptr(char **plus, char **eq, char *clone)
{
	*eq = ft_strchr(clone, '=');
	*plus = NULL;
	if (*eq && *eq > clone && clone[*eq - clone - 1] == '+')
	{
		*plus = *eq - 1;
		**plus = 0;
	}
	if (*eq)
		**eq = 0;
}

static int	free_vars(char *str1, char *str2)
{
	free(str1);
	free(str2);
	return (1);
}

static int	append_to_env_variable(char *name, char *value)
{
	char	*old_value;
	char	*joined;

	old_value = get_env_variable(name);
	if (old_value)
	{
		joined = ft_strjoin(old_value, value);
		free(old_value);
		value = joined;
	}
	set_env_variable(name, value);
	free_vars(name, value);
	return (1);
}

int	export_arg(char *env_line)
{
	int		res;
	char	*eq;
	char	*name;
	char	*clone;
	char	*plus;

	clone = ft_strdup(env_line);
	set_plus_and_eq_ptr(&plus, &eq, clone);
	name = ft_strdup(clone);
	if (!eq)
		return (free_vars(name, clone));
	if (!is_valid_name(name))
		res = 0;
	else if (plus)
		return (append_to_env_variable(name, eq + 1));
	else
	{
		set_env_variable(name, eq + 1);
		res = 1;
	}
	free_vars(name, clone);
	return (res);
}
