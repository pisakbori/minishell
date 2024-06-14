/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:40:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/12 22:08:40 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
