/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:40:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/25 14:19:50 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	delete_value(char *var_name)
{
	char	**env;
	int		i;
	int		j;
	int		size;

	if (str_equal(var_name, "PATH"))
		state()->backup_path = get_env_variable("PATH");
	if (!is_variable(var_name))
		return ;
	env = clone_str_arr(state()->env);
	free_split_arr(state()->env);
	size = ft_arr_len(env) - 1;
	i = -1;
	state()->env = ft_calloc(size + 1, sizeof(char *));
	if (!state()->env)
		exit(EXIT_FAILURE);
	j = 0;
	while (++i <= size)
	{
		if (!(starts_with(env[i], var_name)
				&& env[i][ft_strlen(var_name)] == '='))
			state()->env[j++] = env[i];
	}
}

void	on_unset(t_exec e)
{
	int	i;

	i = 0;
	set_exit_code(0);
	if (e.argc == 1)
	{
		ft_printf(1, "\n");
		return ;
	}
	while (e.argv[++i])
	{
		if (is_valid_name(e.argv[i]))
			delete_value(e.argv[i]);
		else
		{
			set_exit_code(1);
			print_prompt();
			ft_printf(2, "unset: `%s': not a valid identifier\n", e.argv[i]);
		}
	}
}
