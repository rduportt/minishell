/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:10:53 by rduport           #+#    #+#             */
/*   Updated: 2025/07/19 18:10:54 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_outfile_cmd(t_parsing *parsing, int i)
{
	if (parsing[i].outfile[parsing[0].countt.outfile])
	{
		while (parsing[i].outfile[parsing[0].countt.outfile])
		{
			parsing[i].fd = open(parsing[i].outfile[parsing[0].countt.outfile],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (parsing[i].fd == -1)
			{
				perror("minishell: open");
				exit(1);
			}
			dup2(parsing[i].fd, STDOUT_FILENO);
			close(parsing[i].fd);
			parsing[0].countt.outfile++;
		}
	}
}

void	handle_append_cmd(t_parsing *parsing, int i)
{
	if (parsing[i].append[parsing[0].countt.append])
	{
		while (parsing[i].append[parsing[0].countt.append])
		{
			parsing[i].fd = open(parsing[i].append[parsing[0].countt.append],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (parsing[i].fd == -1)
			{
				perror("minishell: open");
				exit(1);
			}
			dup2(parsing[i].fd, STDOUT_FILENO);
			close(parsing[i].fd);
			parsing[0].countt.append++;
		}
	}
}

void	handle_exec(t_parsing *parsing, t_env *envp, int i, int (*pipes)[2])
{
	if (parsing[i].cmd)
	{
		if (!parsing[i].cmd_path || access(parsing[i].cmd_path, X_OK) != 0)
		{
			write(2, "minishell: ", 11);
			write(2, parsing[i].cmd, ft_strlen(parsing[i].cmd));
			write(2, ": command not found\n", 20);
			parsing[0].exit_status = 127;
			free_all(parsing, envp, pipes);
			exit(127);
		}
		else
		{
			parsing[0].exit_status = execve(parsing[i].cmd_path,
					parsing[i].arg, envp->env);
			perror("execve");
			exit(parsing[i].exit_status);
		}
	}
}

void	handle_child_process(t_parsing *parsing,
			int (**pipes)[2], int i, t_env *env)
{
	manage_pipes(parsing, pipes, i);
	if (i > 0)
	{
		dup2((*pipes)[i - 1][0], STDIN_FILENO);
		close((*pipes)[i - 1][0]);
	}
	handle_infile_cmd(parsing, i);
	handle_heredoc_cmd(parsing, i, env, pipes);
	if (i < parsing[0].count - 1)
	{
		close((*pipes)[i][0]);
		dup2((*pipes)[i][1], STDOUT_FILENO);
		close((*pipes)[i][1]);
	}
	handle_outfile_cmd(parsing, i);
	handle_append_cmd(parsing, i);
}

int	wait_and_cleanup(int (**pipes)[2], t_parsing *parsing)
{
	int	status;
	int	i;

	if (*pipes)
	{
		close_all_pipes(*pipes, parsing[0].count - 1);
		free(*pipes);
		*pipes = NULL;
	}
	i = 0;
	status = 0;
	wait_for_children(parsing, i, status);
	signal(SIGINT, handler_sigint);
	return (parsing[0].exit_status);
}
