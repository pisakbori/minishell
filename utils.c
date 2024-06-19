/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:16:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/19 16:57:39 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_error(char *text, int err_code, char *msg)
{
	get_state()->exit_code = err_code;
	if (err_code == 2)
		get_state()->syntax_valid = 0;
	ft_printf(2, "%s: %s", text, msg);
}
