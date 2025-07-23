/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:10:26 by rduport           #+#    #+#             */
/*   Updated: 2025/07/19 18:10:30 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (2);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (3);
	else if (ft_strcmp(cmd, "env") == 0)
		return (4);
	else if (ft_strcmp(cmd, "export") == 0)
		return (5);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (6);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (7);
	return (0);
}

t_env	*exec_builtin(t_parsing *parsing, t_env *env, int i, int (*pipes)[2])
{
	if (parsing->builtin_code == 1)
		parsing[0].exit_status = exec_cd(parsing[i].arg, env, parsing);
	else if (parsing->builtin_code == 2)
		parsing[0].exit_status = actual_path();
	else if (parsing->builtin_code == 3)
		parsing->exit_status = echo(parsing->arg);
	else if (parsing->builtin_code == 4)
		parsing->exit_status = display_env(env->env);
	else if (parsing->builtin_code == 5 && !parsing[i].arg[1])
		parsing->exit_status = display_env(env->export);
	else if (parsing->builtin_code == 5)
		env = ft_export(env, &parsing->arg[1], parsing);
	else if (parsing->builtin_code == 6)
		env = ft_unset(env, &parsing->arg[1]);
	else if (parsing->builtin_code == 7)
		parsing->exit_status = ft_exit(env, pipes, parsing, &parsing[i].arg[1]);
	else
		parsing->exit_status = 1;
	return (env);
}

void	close_all_pipes(int (*pipes)[2], int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	wait_for_children(t_parsing *parsing, int i, int status)
{
	int	sig;

	sig = 0;
	while (i < parsing[0].count)
	{
		if (parsing[i].cmd && !(parsing[i].builtin_code == 1
				|| parsing[i].builtin_code >= 5))
		{
			waitpid(-1, &status, 0);
			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				parsing[0].exit_status = 128 + sig;
				if (sig == SIGQUIT && ft_strcmp(parsing[i].cmd, "cat") == 0
					&& parsing[i].heredoc[0] == NULL)
					write(STDERR_FILENO, "Quit (core dumped)\n", 20);
				else if (sig == SIGINT)
					write(STDERR_FILENO, "\n", 1);
			}
			else if (WIFEXITED(status))
				parsing[0].exit_status = WEXITSTATUS(status);
		}
		i++;
	}
}

int	init_pipes(int (**pipes)[2], t_parsing *parsing)
{
	int	i;

	i = -1;
	*pipes = malloc(2 * sizeof(int) * (parsing[0].count - 1));
	if (!*pipes)
		return (-1);
	while (++i < parsing[0].count - 1)
	{
		if (pipe((*pipes)[i]) == -1)
		{
			perror("minishell: pipe");
			while (--i >= 0)
			{
				close((*pipes)[i][0]);
				close((*pipes)[i][1]);
			}
			free(*pipes);
			return (-1);
		}
	}
	return (0);
}
