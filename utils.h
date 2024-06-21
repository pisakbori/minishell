/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:18:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/20 15:07:52 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

// str_array utils
char	**append_to_str_arr(char **arr, char *str);
void	ft_sort_alph(char **arr);
void	print_array(char **arr);
char	**clone_str_arr(char **arr);

// str utils
char	*ft_str_append(char *str1, char *str2);
char	*next_nonalpha(char *s);
int		starts_with(char *str, char *start);
int		str_equal(char *str1, char *str2);
int		str_has(char *str, char c);
void	ft_replace_chars(char *str, char *map, int c);
int		ends_with_char(char *str, char c);
int		chars_freq(char *str, char *chars);
int		char_freq(char *str, char c);

char	*get_env_variable(char *var_name);
void	ft_free(void **ptr);
void	ft_path_join(char **path, char *bin_name);
int		path_exists(char *path);
int		is_exec(char *path);
int		set_error(char *text, int err_code, char *msg);
char	*get_cmd_path(char *bin_name);

// free_utils
void	free_and_exit(void);
void	free_split_arr(char **res);
void	free_2d_split_arr(char ***res);
char	**split_fail_free(char **res, int i, char *map, char *clone);

int		is_valid_syntax(char *str);

// env
void	set_env_variable(char *var_name, char *var_value);
void	add_value(char *rule);

int		is_variable(char *var_name);

char	*expand_variables(char *str);

char	*skip_until(char quote_type, char *s);
void	arr_expand_variables(char **cmd_set);
char	*remove_chars(char *str, char *skip);
void	arr_remove_chars(char **cmd_set, char *skip);

// expand utils
char	*operation_map(char *str, char *delim, char *skip);
int		append_variable_value(char **res, char **buff, char *str, int *i);
int		start_variable(char *str, char *map, int i);

// split
char	**str_split(char *s, char *delim, char *skip);

// redir
char	**parse_redir(char *str, int index);
int		is_separated_redir(char *symbol, char *arg);
int		is_unsplit_redir(char *str);
int		is_redir_arg(char *str);
int		is_bracket(char *str);
char	*get_arg_name(char *str);
#endif