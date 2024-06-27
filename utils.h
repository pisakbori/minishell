/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:18:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/27 11:52:12 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "enums.h"
# include "minishell.h"

// str_array utils
char	**append_to_str_arr(char **arr, char *str);
void	ft_sort_alph(char **arr);
void	print_array(char **arr);
char	**clone_str_arr(char **arr);
char	*str_join_all(char **arr, char *sepa);

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

// path utils
int		path_exists(char *path);
int		is_exec(char *path);
char	*ft_path_join(char *path, char *bin_name);
void	set_path_error(char *path);

char	*get_env_variable(char *var_name);
void	ft_free(void **ptr);
int		set_error(char *text, int err_code, char *msg);
int		set_mini_error(char *text, int err_code, char *msg);

char	*get_cmd_path(char *bin_name);

// free_utils
void	free_and_exit(void);
void	free_split_arr(char **res);
void	free_2d_split_arr(char ***res);
char	**split_fail_free(char **res, int i, char *map, char *clone);
void	free_pipeline(void);
void	free_redirs(void);

int		syntax_check(char *str);

// env
void	set_env_variable(char *var_name, char *var_value);
void	add_value(char *rule);

int		is_variable(char *var_name);

char	*expand_variables(char *str, char *skip);

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
int		is_unsplit_redir(char *str);
int		is_redir_arg(char *str);
int		is_bracket(char *str);
char	*get_arg_name(char *str);

// parse
void	parse_line(char **cmd_set);
void	set_pipes(char **cmd_set);
void	set_redirs(char **cmd_set);

// heredoc
char	**handle_heredocs(char **stages);
char	*parse_heredoc(char *str, int index);
int		is_separated_heredoc(char *symbol, char *arg);
void	add_separated_heredoc(char *arg, char *map, int i);
void	add_unsplit_heredoc(char *str, char *map, int j, int index);
char	**keep_marked_only(char *map, char **parts);
#endif