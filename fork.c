/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:38:02 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/31 10:21:31 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_ls(char **env)
{
	char	*a[2];

	a[0] = "/bin/ls";
	a[1] = 0;
	execve(a[0], a, env);
	printf("Program still running child\n");
	exit(1);
}

void	run_wc(char **env)
{
	char	*a[2];

	a[0] = "/usr/bin/wc";
	a[1] = 0;
	execve(a[0], a, env);
	perror("wc: ");
	exit(1);
}

int	error_code(int ext)
{
	if (WIFSIGNALED(ext))
		return (128 + WTERMSIG(ext));
	else if (WIFEXITED(ext))
		return (WEXITSTATUS(ext));
	else
		return (ext);
}

/*
0 stdin
1 pipein
2 stderr
3
4
5

*/

int	main(int ai, char **av, char **env)
{
	int fd[2];
	(void)ai;
	(void)av;

	if (pipe(fd) < 0)
	{
		write(2, "pipe\n", 5);
	}

	int pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) < 0)
		{
			write(2, "dup2\n", 5);
		}
		close(fd[1]);
		run_ls(env);
	}
	int pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[1]);
		if (dup2(fd[0], 0) < 0)
		{
			write(2, "dup2\n", 5);
		}
		close(fd[0]);
		// char bf[100];
		// int len = read(0, bf, 10);
		// printf("-%d-\n", len);
		// write(2,bf,10);
		// exit(0);
		run_wc(env);
	}

	close(fd[0]);
	close(fd[1]);

	int exit;

	// kill(pid, SIGINT);
	waitpid(pid, &exit, 0);
	waitpid(pid2, &exit, 0);
	printf("\nProgram still running %d\n", error_code(exit));
}