/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:22:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/24 10:32:49 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char **argv)
{
	char	*cmd;
	int		res;

	if (!argv)
		set_error("minishell", 2, "syntax error");
	if (is_builtin(argv[0]))
		exec_builtin(argv);
	else
	{
		cmd = get_cmd_path(argv[0]);
		if (cmd)
		{
			res = execve(cmd, argv, state()->env);
			set_exit_code(res);
		}
		// else if (state()->cmd_path_status == INVALID_PATH)
		// 	set_error(argv[0], 127, "command not found");
		free(cmd); //TODO: when?????
	}
	exit(state()->exit_code);
}

void	close_unused_pipes(void)
{
	int		i;
	t_pipe	*pipes;

	pipes = state()->pipes;
	i = 0;
	while (pipes[++i].read != -1)
		close_pipe(pipes + i);
}

int	execute_with_pipe(t_stage stage, int i)
{
	int	pid1;

	stage.left_pipe = state()->pipes + i;
	stage.right_pipe = state()->pipes + i + 1;
	pid1 = fork();
	if (!pid1)
	{
		if (i > 0)
			dup2(stage.left_pipe->read, STDIN_FILENO);
		if (i != pipeline_len(state()->pipeline) - 1)
			dup2(stage.right_pipe->write, STDOUT_FILENO);
		close_unused_pipes();
		execute_command(stage.argv);
	}
	return (pid1);
}

void	execute_multiple(int len)
{
	int		i;
	int		*pids;
	int		exit_code;
	t_stage	*pipeline;

	pipeline = state()->pipeline;
	i = -1;
	pids = ft_calloc(len, sizeof(int));
	while (pipeline[++i].argv)
		pids[i] = execute_with_pipe(pipeline[i], i);
	i = -1;
	close_unused_pipes();
	while (pipeline[++i].argv)
		waitpid(pids[i], &exit_code, 0);
	free(pids);
	if (state()->should_stop)
		free_and_exit();
	set_exit_code(error_code(exit_code));
}

void	execute_commands(t_stage *pipeline)
{
	int	len;

	if (!state()->pipeline)
		return ;
	len = pipeline_len(pipeline);
	if (len == 1 && is_builtin(pipeline[0].argv[0]))
		exec_builtin(pipeline[0].argv);
	else
		execute_multiple(len);
}
