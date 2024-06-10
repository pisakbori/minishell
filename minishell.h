/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:40:15 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/10 14:31:00 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "maybe_utils.h"
# include "structs.h"
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
	int	read;
	int	write;
}		t_pipe;
// execution
int		execute_command(char **argv, char **env);
void	execute_cmd(char **argv, t_pipe *left_p, t_pipe *right_p, char **env);
void	execute_commands(char ***cmds_set, char **env, t_pipe *left_p,
			int *exit);
#endif