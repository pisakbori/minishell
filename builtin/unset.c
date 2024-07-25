/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:40:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 13:53:07 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	delete_value(char *var_name)
{
	char	**env;
	int		size;
	int		i;
	int		j;
	int		is_same_var;

	if (!is_variable(var_name))
		return ;
	env = clone_str_arr(state()->env);
	size = ft_arr_len(env) - 1;
	free_split_arr(state()->env);
	state()->env = m_ft_calloc(size + 1, sizeof(char *));
	j = 0;
	i = -1;
	while (++i < size)
	{
		is_same_var = starts_with(env[i], var_name);
		is_same_var = is_same_var && (env[i][ft_strlen(var_name)] == '=');
		if (!is_same_var)
		{
			state()->env[j] = m_ft_strdup(env[i]);
			j++;
		}
	}
	free_split_arr(env);
}

void	on_unset(t_exec e)
{
	int	i;

	i = 0;
	set_exit_code(0);
	if (e.argc == 1)
		return ;
	while (e.argv[++i])
	{
		if (is_valid_name(e.argv[i]))
			delete_value(e.argv[i]);
		else
			set_exit_code(0);
	}
}
