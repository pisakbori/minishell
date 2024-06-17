/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:28:42 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/17 16:37:39 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*get_name_value(char *env_line)
{
	char		*eq;
	t_env_var	*res;
	char		*dup;

	dup = ft_strdup(env_line);
	eq = ft_strchr(dup, '=');
	if (eq)
		*eq = 0;
	res = ft_calloc(1, sizeof(t_env_var));
	res->name = ft_strdup(dup);
	if (!eq)
		res->value = ft_strdup("");
	else
		res->value = ft_strdup(eq + 1);
	free(dup);
	return (res);
}

char	**clone_str_arr(char **arr)
{
	int		i;
	int		size;
	char	**new;

	size = ft_arr_len(arr);
	i = -1;
	new = ft_calloc(size + 1, sizeof(char *));
	if (!new)
		exit(EXIT_FAILURE);
	while (arr && arr[++i])
	{
		new[i] = ft_strdup(arr[i]);
	}
	return (new);
}
char	**append_to_str_arr(char **arr, char *str)
{
	int		i;
	int		size;
	char	**new;

	size = ft_arr_len(arr) + 1;
	new = ft_calloc(size + 1, sizeof(char *));
	if (!new)
		exit(EXIT_FAILURE);
	i = 0;
	while (arr && arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	free_split_arr(arr);
	new[i] = ft_strdup(str);
	return (new);
}

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

void	delete_value(char *var_name)
{
	char	**env;
	t_state	*state;
	int		i;
	int		j;
	int		size;

	if (!is_variable(var_name))
		return ;
	state = get_state();
	env = clone_str_arr(state->env);
	free_split_arr(state->env);
	size = ft_arr_len(env) - 1;
	i = -1;
	state->env = ft_calloc(size + 1, sizeof(char *));
	if (!state->env)
		exit(EXIT_FAILURE);
	j = 0;
	while (++i <= size)
	{
		if (!(starts_with(env[i], var_name)
				&& env[i][ft_strlen(var_name)] == '='))
			state->env[j++] = env[i];
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

void	set_oldpwd(char *oldcwd)
{
	t_state	*state;

	state = get_state();
	set_env_variable("OLDPWD", oldcwd);
	free(state->oldcwd);
	state->oldcwd = ft_strdup(oldcwd);
}

void	set_cwd(char *cwd)
{
	t_state *state;

	state = get_state();
	set_oldpwd(state->cwd);
	free(state->cwd);
	state->cwd = ft_strdup(cwd);
	set_env_variable("PWD", cwd);
}