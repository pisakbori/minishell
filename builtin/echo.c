/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:27:44 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/01 13:56:22 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//	echo
//	echo ~ , even if home is unset
//	echo -nnnnn -n -n test
//	echo -nnnnnadsfasdadasdasda -n -n -n test
//	echo -asghhjgjf
int	is_n_flag(char *option)
{
	int	i;

	if (!option)
		return (0);
	if (option[0] != '-')
		return (0);
	i = 1;
	while (option[i] == 'n')
		i++;
	if (option[i] != 0 || i == 1)
		return (0);
	else
		return (1);
}

void	on_echo(t_exec e)
{
	int	i;
	int	skip_nl;

	skip_nl = 0;
	if (e.argc == 1)
		ft_printf(1, "\n");
	else
	{
		i = 1;
		while ((i == 1 || skip_nl) && is_n_flag(e.argv[i]))
		{
			i++;
			skip_nl = 1;
		}
		while (i < e.argc)
		{
			ft_printf(1, "%s", e.argv[i++]);
			if (i < e.argc)
				ft_printf(1, " ");
		}
		if (!skip_nl)
			ft_printf(1, "\n");
	}
	set_exit_code(0);
}
