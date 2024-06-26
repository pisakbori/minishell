/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:40:15 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/26 15:20:07 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "enums.h"
# include "utils.h"
# include <builtins.h>
# include <errno.h>
# include <fcntl.h>
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
	int				read;
	int				write;
}					t_pipe;

typedef struct s_env_var
{
	char			*name;
	char			*value;
}					t_env_var;

typedef struct s_redir
{
	char			*in;
	int				in_mode;
	int				in_fd;
	char			*out;
	int				out_mode;
	int				out_fd;
	int				invalid;
}					t_redir;

typedef struct s_stage
{
	t_redir			redir;
	char			**argv;
	t_pipe			*left_pipe;
	t_pipe			*right_pipe;
}					t_stage;

typedef struct s_state
{
	int				should_stop;
	t_path_status	path_status;
	t_stage			*pipeline;
	t_pipe			*pipes;
	int				exit_code;
	char			**env;
	char			*backup_path;
	char			*last_arg;
	char			*oldcwd;
	char			*cwd;
	t_redir			*redirs;
	int				backup_stdin;
	int				backup_stdout;
	char			*heredoc_dir;
}					t_state;

// execution
void				execute_commands(t_stage *pipeline);
void				close_pipe(t_pipe *p);
int					pipeline_len(t_stage *pipeline);
t_pipe				invalid_pipe(void);
void				close_read(t_pipe *p);
void				close_write(t_pipe *p);

int					error_code(int ext);

void				init_state(int argc, char const *argv[], char **env);
void				set_exit_code(int exit_code);
void				set_state(t_state *val);
t_state				*state(void);
t_state				**get_state_ptr(void);
void				set_last_arg(char *arg);
void				set_cwd(char *cwd);
void				reset_state(void);
void				reset_stdio(void);

void				print_prompt(void);

#endif