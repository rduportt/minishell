/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:31:24 by rduport           #+#    #+#             */
/*   Updated: 2025/07/24 16:31:25 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_commands(t_parsing *parsing, t_env *envp)
{
	int	i;

	i = 0;
	if (!parsing)
		return (-1);
	parsing[i].cmd_path = NULL;
	while (parsing[i].cmd != NULL)
	{
		parsing[0].pid = 0;
		parsing[i].cmd_path = NULL;
		parsing[i].builtin_code = is_built_in(parsing[i].cmd);
		if (parsing[i].builtin_code == 0)
		{
			if (is_direct_path(parsing[i].cmd))
			{
				if (access(parsing[i].cmd, F_OK) == 0)
					parsing[i].cmd_path = ft_strdup(parsing[i].cmd);
			}
			else
				parsing[i].cmd_path = find_path(envp->env, parsing[i].cmd);
		}
		i++;
	}
	return (1);
}

void	free_all_heredoc(t_parsing *parsing, t_env *env,
			int (**pipes)[2], int heredoc_pipe[2])
{
	if (*pipes)
	{
		close_all_pipes(*pipes, parsing[0].count - 1);
		free(*pipes);
		*pipes = NULL;
	}
	if (env->env)
		free_tab(env->env);
	if (env->export)
		free_tab(env->export);
	free(env);
	close(1);
	close(2);
	close(heredoc_pipe[0]);
	close(heredoc_pipe[1]);
	free_parsing(parsing);
	exit(130);
}

void	free_all(t_parsing *parsing, t_env *env, int (*pipes)[2])
{
	if (pipes)
	{
		close_all_pipes(pipes, parsing[0].count - 1);
		free(pipes);
		pipes = NULL;
	}
	if (env->env)
		free_tab(env->env);
	if (env->export)
		free_tab(env->export);
	free(env);
	close(0);
	close(1);
	close(2);
	free_parsing(parsing);
}
