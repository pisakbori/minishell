/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:18:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/17 22:11:55 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

char		*get_env_variable(char *var_name);
void		print_array(char **arr);
void		ft_free(void **ptr);
void		ft_path_join(char **path, char *bin_name);
int			path_exists(char *path);
int			is_exec(char *path);
void		set_error(char *text, int err_code);
int			ends_with_char(char *str, char c);
char		*get_cmd_path(char *bin_name);
int			str_equal(char *str1, char *str2);
int			starts_with(char *str, char *start);
void		ft_sort_alph(char **arr);

// free_utils
void		free_and_exit(void);
void		free_split_arr(char **res);
void		free_2d_split_arr(char ***res);

char		**ft_split2(char *s, char *delim, char mode);
int			is_valid_syntax(char *str);

// env
t_env_var	*get_name_value(char *env_line);
void		set_env_variable(char *var_name, char *var_value);
void		delete_value(char *var_name);
void		add_value(char *rule);
char		**clone_str_arr(char **arr);
int			is_variable(char *var_name);

char		*expand_variables(char *str);
typedef enum
{
	TERMINATOR,
	SKIP,
	KEEP,
	VAR_NAME
}			status;
char		*skip_quote(char quote_type, char *s);
#endif