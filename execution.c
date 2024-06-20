/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:22:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/20 12:46:29 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(char **argv)
{
	char	*cmd;
	int		res;
	char	**env;

	env = get_state()->env;
	if (!argv)
	{
		ft_printf(2, "Syntax error");
		return (2);
	}
	cmd = get_cmd_path(argv[0]);
	if (cmd)
		res = execve(cmd, argv, env);
	else
	{
		ft_printf(2, "%s: command not found\n", argv[0]);
		res = 127;
	}
	free(cmd); //TODO: when?????
	return (res);
}

void	execute_cmd(t_stage stage, t_pipe *left_p, t_pipe *right_p)
{
	int	res;

	// printf("%s in: %s\n", stage.argv[0], stage.redir.in);
	// printf("%s out: %s\n", stage.argv[0], stage.redir.out);
	if (right_p)
	{
		close(right_p->read);
		if (dup2(right_p->write, 1) == -1)
			set_error("dup2 right", 0, NULL);
		close(right_p->write);
	}
	if (left_p)
	{
		close(left_p->write);
		if (dup2(left_p->read, 0) == -1)
			set_error("dup2 left", 0, NULL);
		close(left_p->read);
	}
	res = execute_command(stage.argv);
	exit(res);
}

void	execute_rightmost(t_stage stage, t_pipe *left_p)
{
	t_pipe	*right_p;
	int		fd[2];
	int		pid1;
	int		exit;

	if (is_builtin(stage.argv[0]))
	{
		exec_builtin(stage.argv);
		return ;
	}
	exit = get_state()->exit_code;
	if (pipe(fd) < 0)
		set_error("pipe", 0, NULL);
	right_p = &(t_pipe){.read = fd[0], .write = fd[1]};
	pid1 = fork();
	right_p->read = dup(0);
	right_p->write = dup(1);
	if (!pid1)
		execute_cmd(stage, left_p, right_p);
	close_pipe(left_p);
	close_pipe(right_p);
	waitpid(pid1, &exit, 0);
	set_exit_code(error_code(exit));
	set_last_arg(stage.argv[ft_arr_len(stage.argv) - 1]);
}

void	execute_with_pipe(t_stage *pipeline, t_pipe *left_p)
{
	int		temp;
	t_pipe	*right_p;
	int		fd[2];
	int		pid1;

	if (pipe(fd) < 0)
		set_error("pipe", 0, NULL);
	right_p = &(t_pipe){.read = fd[0], .write = fd[1]};
	pid1 = fork();
	if (!pid1)
		execute_cmd(*pipeline, left_p, right_p);
	close_pipe(left_p);
	execute_commands(pipeline + 1, right_p);
	close_pipe(right_p);
	waitpid(pid1, &temp, 0);
}
int	pipeline_len(t_stage *pipeline)
{
	int	len;

	len = 0;
	if (!pipeline)
		return (0);
	while (pipeline[len].argv)
		len++;
	return (len);
}

void	execute_commands(t_stage *pipeline, t_pipe *left_p)
{
	if (!pipeline || !get_state()->syntax_valid)
		return ;
	if (pipeline_len(pipeline) > 1)
		execute_with_pipe(pipeline, left_p);
	else
		execute_rightmost(pipeline[0], left_p);
}
