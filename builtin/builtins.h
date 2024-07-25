/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:39:48 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/25 12:27:47 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <enums.h>
# include <minishell.h>

typedef struct s_exec
{
	int		argc;
	char	**argv;
}			t_exec;

// builtins
int			is_builtin(char *cmd);
int			exec_builtin(char **argv);
void		on_exit_b(t_exec e);
void		on_cd(t_exec e);
void		on_pwd(t_exec e);
void		on_env(t_exec e);
void		on_export(t_exec e);
int			export_arg(char *env_line);
void		on_echo(t_exec e);
void		on_unset(t_exec e);
int			is_valid_name(char *name);

int			is_valid_path(char *path);
int			is_dir(char *path);
void		print_err_prompt(void);

#endif