/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:47:59 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/07/24 13:53:13 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	**get_state_ptr(void)
{
	static t_state	*state;

	return (&state);
}

t_state	*state(void)
{
	return (*get_state_ptr());
}

void	inc_shell_level(void)
{
	char	*str_shlvl;
	int		shlvl;

	str_shlvl = get_env_variable("SHLVL");
	shlvl = 0;
	if (str_shlvl)
		shlvl = ft_atoi(str_shlvl);
	free(str_shlvl);
	shlvl++;
	str_shlvl = ft_itoa(shlvl);
	set_env_variable("SHLVL", str_shlvl);
	free(str_shlvl);
}

void	init_state(int argc, char const *argv[], char **env)
{
	t_state	*state;
	char	cwd[4096];
	char	basic_path[61];

	(void)argc;
	(void)argv;
	state = ft_calloc(1, sizeof(t_state));
	state->n_heredocs = 0;
	state->path_status = IS_VALID;
	state->exit_code = 0;
	state->env = clone_str_arr(env);
	getcwd(cwd, 4096);
	state->cwd = ft_strdup(cwd);
	state->backup_stdin = dup(STDIN_FILENO);
	state->backup_stdout = dup(STDOUT_FILENO);
	state->should_stop = 0;
	state->pipeline = NULL;
	*get_state_ptr() = state;
	state->home_backup = get_env_variable("HOME");
	inc_shell_level();
	if (!*env)
	{
		ft_strlcpy(basic_path, "/usr/local/sbin:/usr/local/bin:", 61);
		ft_strlcpy(basic_path + 31, "/usr/sbin:/usr/bin:/sbin:/bin", 30);
		set_env_variable("PATH", basic_path);
	}
}
void	reset_stdio(void)
{
	dup2(state()->backup_stdin, STDIN_FILENO);
	dup2(state()->backup_stdout, STDOUT_FILENO);
}

void	reset_state(void)
{
	remove_all_heredocs(state()->n_heredocs);
	reset_stdio();
	free_pipeline();
	state()->path_status = IS_VALID;
	state()->n_heredocs = 0;
}
