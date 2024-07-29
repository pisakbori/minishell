/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:28:42 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/29 10:45:52 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	add_value(char *rule)
{
	char	**env;
	char	**new;
	t_state	*s;

	s = state();
	env = clone_str_arr(s->env);
	free_split_arr(s->env);
	new = append_to_str_arr(env, rule);
	s->env = new;
}

void	replace_value(char *var_name, char *rule)
{
	t_state	*s;
	int		i;
	char	length_ok;
	int		len;

	if (!is_variable(var_name))
		return ;
	s = state();
	i = -1;
	len = ft_strlen(var_name);
	while (s->env[++i])
	{
		length_ok = (ft_strlen(s->env[i]) - len > 0);
		length_ok = length_ok && s->env[i][len] == '=';
		if (starts_with(s->env[i], var_name) && length_ok)
		{
			free(s->env[i]);
			s->env[i] = m_ft_strdup(rule);
			return ;
		}
	}
}

void	set_env_variable(char *var_name, char *var_value)
{
	char	*rule;
	char	*temp;

	if (str_equal(var_name, "_"))
		set_last_arg(var_value);
	temp = m_ft_strjoin(var_name, "=");
	rule = m_ft_strjoin(temp, var_value);
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
	env = state()->env;
	if (str_equal(var_name, "~"))
		return (m_ft_strdup(state()->home_backup));
	while (env[++i])
	{
		clone = m_ft_strdup(env[i]);
		if (clone[name_len] == '=')
		{
			clone[name_len] = 0;
			if (str_equal(clone, var_name))
				res = m_ft_strdup(clone + name_len + 1);
		}
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
	env = state()->env;
	while (env[++i])
	{
		clone = m_ft_strdup(env[i]);
		clone[name_len] = 0;
		if (str_equal(clone, var_name) && env[i][name_len] == '=')
		{
			free(clone);
			return (1);
		}
		free(clone);
	}
	return (0);
}
