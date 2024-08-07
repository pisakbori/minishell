/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:03:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/26 11:26:37 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env_var	*get_name_value(char *env_line)
{
	char		*eq;
	t_env_var	*res;
	char		*dup;

	dup = m_ft_strdup(env_line);
	eq = ft_strchr(dup, '=');
	if (eq)
		*eq = 0;
	res = m_ft_calloc(1, sizeof(t_env_var));
	res->name = m_ft_strdup(dup);
	if (!eq)
		res->value = m_ft_strdup("");
	else
		res->value = m_ft_strdup(eq + 1);
	free(dup);
	return (res);
}

void	print_all_exported(void)
{
	char		**env;
	char		**copy;
	int			i;
	t_env_var	*en;

	env = state()->env;
	i = -1;
	copy = clone_str_arr(env);
	ft_sort_alph(copy);
	i = -1;
	while (copy[++i])
	{
		en = get_name_value(copy[i]);
		if (!str_equal(en->name, "_"))
			ft_printf(1, "declare -x %s=\"%s\"\n", en->name, en->value);
		free(en->name);
		free(en->value);
		free(en);
	}
	free_split_arr(copy);
}

// If no names are supplied, a list of names of
// all exported variables is displayed.
// The return status is zero unless --- one of
// the names is not a valid shell variable name
void	on_export(t_exec e)
{
	int	i;
	int	all_correct;

	(void)e;
	if (e.argc == 1)
		print_all_exported();
	all_correct = 1;
	i = 0;
	while (++i < e.argc)
	{
		if (!export_arg(e.argv[i]))
		{
			print_err_prompt();
			ft_printf(2, "export: `%s': not a valid identifier\n", e.argv[i]);
			all_correct = 0;
		}
	}
	if (!all_correct)
		set_exit_code(1);
	else
		set_exit_code(0);
}
