/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:22:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:27 by bpisak-l         ###   ########.fr       */
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
		if (*buff)
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

void	close_redir(t_stage stage)
{
	if (stage.redir.in_fd && stage.redir.in_fd != -1)
		close(stage.redir.in_fd);
	if (stage.redir.out_fd && stage.redir.out_fd != -1)
		close(stage.redir.out_fd);
}

void	close_all_redir(void)
{
	t_stage	*pipeline;

	pipeline = state()->pipeline;
	while (pipeline->argv)
	{
		if (pipeline->redir.in_fd || pipeline->redir.out_fd)
			close_redir(*pipeline);
		pipeline++;
	}
}

void	handle_redir(t_stage *s)
{
	int	out_mode;

	reset_stdio();
	if (s->redir.in)
	{
		s->redir.in_fd = open(s->redir.in, O_RDONLY, S_IRWXU);
		if (s->redir.in_fd != -1)
		{
			dup2(s->redir.in_fd, STDIN_FILENO);
			close(s->redir.in_fd);
		}
		else
			set_error("minishell", 1, "Permission denied");
	}
	if (s->redir.out)
	{
		out_mode = O_CREAT | O_WRONLY | s->redir.out_mode;
		s->redir.out_fd = open(s->redir.out, out_mode, S_IRWXU);
		if (s->redir.out_fd != -1)
		{
			dup2(s->redir.out_fd, STDOUT_FILENO);
			close(s->redir.out_fd);
		}
		else
			set_error("minishell", 1, "Permission denied");
	}
}

int	execute_with_pipe(t_stage *stage, int i)
{
	int	pid1;

	stage->left_pipe = state()->pipes + i;
	stage->right_pipe = state()->pipes + i + 1;
	handle_redir(stage);
	pid1 = fork();
	if (!pid1)
	{
		if (stage->redir.in_fd == -1 || stage->redir.out_fd == -1)
			exit(1);
		if (i > 0 && !stage->redir.in)
			dup2(stage->left_pipe->read, STDIN_FILENO);
		if (!stage->redir.out && i != pipeline_len(state()->pipeline) - 1)
			dup2(stage->right_pipe->write, STDOUT_FILENO);
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
	pids = ft_calloc(len, sizeof(int));
	while (pipeline[++i].argv)
		pids[i] = execute_with_pipe(pipeline + i, i);
	i = -1;
	close_all_pipes();
	close_all_redir();
	while (pipeline[++i].argv)
		if (pids[i] != -1)
			waitpid(pids[i], &exit_code, 0);
	free(pids);
	if (state()->should_stop)
		free_and_exit();
	set_exit_code(error_code(exit_code));
}

void	execute_commands(t_stage *pipeline)
{
	int	len;

	len = pipeline_len(pipeline);
	if (len == 1 && is_builtin(pipeline[0].argv[0]))
	{
		handle_redir(pipeline);
		exec_builtin(pipeline[0].argv);
		close_redir(pipeline[0]);
	}
	else
	{
		execute_multiple(len);
	}
}
