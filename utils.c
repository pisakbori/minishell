/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:16:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/18 15:03:03 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_error(char *text, int err_code)
{
	// TODO: set last errorcode to err_code
	(void)err_code;
	ft_printf(2, "%s: ", text);
	perror(NULL);
}
