/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:40:15 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/20 12:27:47 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "maybe_utils.h"
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
	int			read;
	int			write;
}				t_pipe;

typedef enum mode
{
	TRUNCATE,
	APPEND
}				t_file_mode;

typedef enum redir
{
	IN,
	OUT
}				t_redir_io;

typedef enum operation
{
	END,
	KEEP,
	DELIMITER,
	SKIP,
}				t_operation;

typedef struct s_redir
{
	char		*in;
	t_file_mode	in_mode;
	char		*out;
	t_file_mode	out_mode;
}				t_redir;

typedef struct s_stage
{
	t_redir		redir;
	char		**argv;
}				t_stage;

typedef struct s_state
{
	t_stage		*pipeline;
	int			exit_code;
	int			syntax_valid;
	char		**env;
	char		**path;
	char		*last_arg;
	char		*oldcwd;
	char		*cwd;
	t_redir		*redirs;
	int			backup_stdin;
	int			backup_stdout;
}				t_state;

// execution
void			execute_commands(t_stage *pipeline, t_pipe *left_p);
void			close_pipe(t_pipe *p);

int				error_code(int ext);

void			init_state(char **env);
void			set_exit_code(int exit_code);
void			set_state(t_state *val);
t_state			*get_state(void);
t_state			**get_state_ptr(void);
void			set_last_arg(char *arg);
void			set_cwd(char *cwd);
void			reset_stdio(void);

void			print_prompt(void);

#endif