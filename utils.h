/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:18:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/31 20:04:57 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

char	*get_env_variable(char *var_name, char **env);
void	print_array(char **arr);
void	ft_free(void **ptr);
void	ft_path_join(char **path, char *bin_name);
int		path_exists(char *path);
int		is_exec(char *path);
void	set_error(char *text, int err_code);
int		starts_with(char *str, char *start);

#endif