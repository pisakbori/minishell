/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:22:52 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/06/24 14:07:01 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char **argv)
{
	char	buff[4096];
	char	*cmd;
	int		res;

	if (!argv)
		set_error("minishell", 2, "syntax error");
	if (is_builtin(argv[0]))
		exec_builtin(argv);
	else
	{
		cmd = get_cmd_path(argv[0]);
		ft_strlcpy(buff, cmd, 4096);
		free(cmd);
		if (*buff)
		{
			res = execve(buff, argv, state()->env);
			set_exit_code(res);
		}
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
	if (stage.redir.in_fd)
		close(stage.redir.in_fd);
	if (stage.redir.out_fd)
		close(stage.redir.out_fd);
}
void	handle_redir(t_redir *r)
{
	int	out_mode;

	if (r->in)
	{
		r->in_fd = open(r->in, O_RDONLY, S_IRWXU);
		if (r->in_fd != -1)
		{
			dup2(r->in_fd, STDIN_FILENO);
			close(r->in_fd);
		}
	}
	if (r->out)
	{
		out_mode = O_CREAT | O_WRONLY | r->out_mode;
		r->out_fd = open(r->out, out_mode, S_IRWXU);
		if (r->out_fd != -1)
		{
			dup2(r->out_fd, STDOUT_FILENO);
			close(r->out_fd);
		}
	}
}

int	execute_with_pipe(t_stage *stage, int i)
{
	int	pid1;

	stage->left_pipe = state()->pipes + i;
	stage->right_pipe = state()->pipes + i + 1;
	pid1 = fork();
	if (!pid1)
	{
		handle_redir(&stage->redir);
		if (i > 0 && !stage->redir.in)
			dup2(stage->left_pipe->read, STDIN_FILENO);
		if (!stage->redir.out && i != pipeline_len(state()->pipeline) - 1)
			dup2(stage->right_pipe->write, STDOUT_FILENO);
		close_all_pipes();
		execute_command(stage->argv);
	}
	return (pid1);
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
	{
		handle_redir(&pipeline[0].redir);
		exec_builtin(pipeline[0].argv);
		close_redir(pipeline[0]);
	}
	else
		execute_multiple(len);
}
