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
	if ((parsing[i].builtin_code == 1 || parsing[i].builtin_code >= 5))
	{
		envp = exec_builtin(&parsing[i], envp, i, pipes);
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	parsing[0].pid = fork();
	return (0);
}

int	init_process_command(t_parsing *parsing,
		t_env *envp, int (*pipes)[2], int i)
{
	parsing[0].countt = count_init();
	if (!parsing[i].cmd)
		return (handle_empty_cmd(parsing, i));
	if (check_built_in(parsing, envp, i, pipes) == 1)
		return (1);
	if (parsing[0].pid == -1)
		return (-1);
	return (0);
}

int	process_command(t_parsing *parsing, t_env *envp, int (*pipes)[2], int i)
{
	int		buffer;

	buffer = init_process_command(parsing, envp, pipes, i);
	if (buffer != 0)
		return (buffer);
	if (parsing[0].pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_child_process(parsing, &pipes, i, envp);
		if (parsing[i].builtin_code <= 4 && parsing[i].builtin_code != 0)
		{
			envp = exec_builtin(&parsing[i], envp, i, pipes);
			buffer = parsing[i].exit_status;
			free_all(parsing, envp, pipes);
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
