/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:16:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/26 11:58:29 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	set_error(char *text, int err_code, char *msg)
{
	state()->exit_code = err_code;
	ft_printf(2, "%s: %s\n", text, msg);
	return (err_code);
}

int	set_mini_error(char *text, int err_code, char *msg)
{
	ft_printf(2, "minishell: ");
	return (set_error(text, err_code, msg));
}
