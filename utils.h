/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:18:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/12 10:12:08 by bpisak-l         ###   ########.fr       */
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
int		ends_with_char(char *str, char c);
char	*get_cmd_path(char *bin_name, char **env);
int		str_equal(char *str1, char *str2);
char	**ft_split_and_keep(char const *s, char *delim);

// free_utils
void	free_split_arr(char **res);
void	free_2d_split_arr(char ***res);

char	**ft_split2(char *s, char *delim);

#endif