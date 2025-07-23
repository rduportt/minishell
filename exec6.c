/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:11:00 by rduport           #+#    #+#             */
/*   Updated: 2025/07/19 18:11:01 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built_in(t_parsing *parsing, t_env *envp, int i, int (*pipes)[2])
{
	if ((parsing[i].builtin_code == 1 || parsing[i].builtin_code > 5) || (parsing[i].builtin_code == 5 && parsing[i].arg[1]))
	{
		envp = exec_builtin(&parsing[i], envp, i, pipes);
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	g_child_pid = fork();
	return (0);
}

void cleanup_pipes(int (**pipes)[2], t_parsing *parsing)
{
    if (*pipes && parsing) {
        close_all_pipes(*pipes, parsing[0].count - 1);
        free(*pipes);
        *pipes = NULL;
    }
}

int	process_command(t_parsing *parsing, t_env *envp, int (*pipes)[2], int i)
{
	t_count	count;
	int		buffer;

	count = count_init();
	if (!parsing[i].cmd)
		return (handle_empty_cmd(parsing, count, i));
	if (check_built_in(parsing, envp, i, pipes) == 1)
		return (1);
	if (g_child_pid == -1)
		return (-1);
	if (g_child_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_child_process(parsing, count, &pipes, i);
		if ((parsing[i].builtin_code <= 4 || (parsing[i].builtin_code == 5 && !parsing[i].arg[1])) && parsing[i].builtin_code != 0)
		{
			envp = exec_builtin(&parsing[i], envp, i, pipes);
			buffer = parsing[i].exit_status;
			if (envp->env)
				free_tab(envp->env);
			if (envp->export)
				free_tab(envp->export);
			free(envp);
			if (pipes)
			{
				close_all_pipes(pipes, parsing[0].count - 1);
				free(pipes);
				pipes = NULL;
			}
			free_parsing(parsing);
			close(0);
			close(1);
			close(2);
			exit(buffer);
		}
		else
			handle_exec(parsing, envp, i, pipes);
	}
	return (1);
}

int	handle_execution(t_parsing *parsing, t_env *envp, int (*pipes)[2])
{
	int	i;

	i = 0;
	while (i < parsing[0].count)
	{
		if (!process_command(parsing, envp, pipes, i))
			return (0);
		i++;
	}
	return (1);
}

int	exec_cmd(t_parsing *parsing, t_env *envp)
{
	int	(*pipes)[2];

	if (init_pipes(&pipes, parsing) == -1)
		return (-1);
	if (!handle_execution(parsing, envp, pipes))
		return (0);
	return (wait_and_cleanup(&pipes, parsing));
}

int	prepare_commands(t_parsing *parsing, t_env *envp)
{
	int	i;

	i = 0;
	if (!parsing)
		return (-1);
	parsing[i].cmd_path = NULL;
	while (parsing[i].cmd != NULL)
	{
		g_child_pid = 0;
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
