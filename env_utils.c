/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:28:42 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/18 15:24:07 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	add_value(char *rule)
{
	char	**env;
	char	**new;
	t_state	*state;

	state = get_state();
	env = clone_str_arr(state->env);
	free_split_arr(state->env);
	new = append_to_str_arr(env, rule);
	state->env = new;
}

void	replace_value(char *var_name, char *rule)
{
	t_state	*state;
	int		i;

	if (!is_variable(var_name))
		return ;
	state = get_state();
	i = -1;
	while (state->env[++i])
	{
		if (starts_with(state->env[i], var_name)
			&& state->env[i][ft_strlen(var_name)] == '=')
		{
			free(state->env[i]);
			state->env[i] = ft_strdup(rule);
		}
	}
}

void	set_env_variable(char *var_name, char *var_value)
{
	char	*rule;
	char	*temp;

	if (str_equal(var_name, "_"))
		set_last_arg(var_value);
	temp = ft_strjoin(var_name, "=");
	rule = ft_strjoin(temp, var_value);
	if (!is_variable(var_name))
		add_value(rule);
	else
		replace_value(var_name, rule);
	free(temp);
	free(rule);
}

char	*get_env_variable(char *var_name)
{
	char	**env;
	int		i;
	int		name_len;
	char	*clone;
	char	*res;

	i = -1;
	res = NULL;
	name_len = ft_strlen(var_name);
	env = get_state()->env;
	while (env[++i])
	{
		clone = ft_strdup(env[i]);
		clone[name_len] = 0;
		if (str_equal(clone, var_name))
			res = ft_strdup(clone + name_len + 1);
		free(clone);
	}
	return (res);
}

int	is_variable(char *var_name)
{
	char	**env;
	int		i;
	int		name_len;
	char	*clone;

	i = -1;
	name_len = ft_strlen(var_name);
	env = get_state()->env;
	while (env[++i])
	{
		clone = ft_strdup(env[i]);
		clone[name_len] = 0;
		if (str_equal(clone, var_name))
			return (1);
		free(clone);
	}
	return (0);
}
