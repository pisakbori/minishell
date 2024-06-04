/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maybe_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:17:59 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/04 11:26:26 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAYBE_UTILS_H
# define MAYBE_UTILS_H

# include "minishell.h"

typedef struct s_env_var
{
	char	*name;
	char	*value;
}			t_env_var;

void		print_arr(char **arr);

#endif