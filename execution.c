/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:22:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/26 11:51:41 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char **argv)
{
	char	buff[4096];
	char	*cmd;

	if (!argv)
		set_error("minishell", 2, "syntax error");
	if (is_builtin(argv[0]))
		exec_builtin(argv);
	else if (!argv[0])
		set_exit_code(0);
	else
	{
		cmd = get_cmd_path(argv[0]);
		ft_strlcpy(buff, cmd, 4096);
		if (cmd)
			free(cmd);
		if (buff[0])
			execve(buff, argv, state()->env);
	}
	exit(state()->exit_code);
}

void	close_all_pipes(void)
{
	int		i;
	t_pipe	*pipes;

	pipes = state()->pipes;
	i = 0;
	while (pipes[++i].read != -1)
		close_pipe(pipes + i);
}

int	execute_with_pipe(t_stage *stage, int i)
{
	int	pid1;

	stage->left_pipe = state()->pipes + i;
	stage->right_pipe = state()->pipes + i + 1;
	pid1 = fork();
	if (!pid1)
	{
		if (stage->redir.invalid)
			exit(1);
		default_signals();
		if (!set_redir_in(stage) && i > 0)
			m_dup2(stage->left_pipe->read, STDIN_FILENO);
		if (!set_redir_out(stage) && (i != pipeline_len(state()->pipeline) - 1))
			m_dup2(stage->right_pipe->write, STDOUT_FILENO);
		close_all_pipes();
		close_all_redir();
		execute_command(stage->argv);
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
	pids = m_ft_calloc(len, sizeof(int));
	while (pipeline[++i].argv)
		pids[i] = execute_with_pipe(pipeline + i, i);
	i = -1;
	close_all_pipes();
	close_all_redir();
	while (pipeline[++i].argv)
		if (pids[i] != -1)
			waitpid(pids[i], &exit_code, 0);
	free(pids);
	set_exit_code(error_code(exit_code));
}

void	execute_commands(t_stage *pipeline)
{
	int	len;
	int	last_arg_index;

	len = pipeline_len(pipeline);
	last_arg_index = ft_arr_len(pipeline[len - 1].argv);
	if (len == 1 && last_arg_index)
		set_last_arg(pipeline[len - 1].argv[last_arg_index - 1]);
	if (len == 1 && is_builtin(pipeline[0].argv[0]))
	{
		set_redir_in(pipeline);
		set_redir_out(pipeline);
		if (!pipeline[0].redir.invalid)
			exec_builtin(pipeline[0].argv);
		close_redir(pipeline[0]);
	}
	else
		execute_multiple(len);
}
