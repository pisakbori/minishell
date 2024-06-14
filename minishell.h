/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:40:15 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/14 17:14:22 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "maybe_utils.h"
# include "utils.h"
# include <builtins.h>
# include <errno.h>
# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>   //for strerror
# include <sys/stat.h> //for stat, for dirs
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe
{
	int		read;
	int		write;
}			t_pipe;

typedef struct s_state
{
	int		exit_code;
	char	**env;
	char	**path;
	char	*last_arg;
	char	*oldcwd;
	char	*cwd;
}			t_state;
// execution
int			execute_command(char **argv);
void		execute_cmd(char **argv, t_pipe *left_p, t_pipe *right_p);
void		execute_commands(char ***cmds_set, t_pipe *left_p);

void		set_exit_code(int exit_code);
void		set_state(t_state *val);
t_state		*get_state(void);
t_state		**get_state_ptr(void);
void		set_env(char **env);
void		set_last_arg(char *arg);

void		print_prompt(void);

#endif