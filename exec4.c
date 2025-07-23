/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:10:46 by rduport           #+#    #+#             */
/*   Updated: 2025/07/19 18:10:47 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_empty_cmd(t_parsing *parsing, int i)
{
	handle_heredoc_no_cmd(parsing, i);
	if (g_child_pid == 130)
	{
		parsing[0].exit_status = 130;
		g_child_pid = 0;
		return (130);
	}
	handle_append_no_cmd(parsing, i);
	handle_infile_no_cmd(parsing, i);
	handle_outile_no_cmd(parsing, i);
	return (1);
}

void	manage_pipes(t_parsing *parsing, int (**pipes)[2], int i)
{
	int	j;

	j = -1;
	while (++j < parsing[0].count - 1)
	{
		if (i > 0 && j == i - 1)
			continue ;
		if (i < parsing[0].count - 1 && j == i)
			continue ;
		close((*pipes)[j][0]);
		close((*pipes)[j][1]);
	}
	if (i > 0)
	{
		close((*pipes)[i - 1][1]);
		dup2((*pipes)[i - 1][0], STDIN_FILENO);
		close((*pipes)[i - 1][0]);
	}
}

void	handle_infile_cmd(t_parsing *parsing, int i)
{
	if (parsing[i].infile[parsing[0].countt.infile])
	{
		while (parsing[i].infile[parsing[0].countt.infile])
		{
			parsing[i].fd = open(parsing[i].infile[parsing[0].countt.infile],
					O_RDONLY);
			if (parsing[i].fd == -1)
			{
				perror("minishell: open");
				exit (1);
			}
			dup2(parsing[i].fd, STDIN_FILENO);
			close(parsing[i].fd);
			parsing[0].countt.infile++;
		}
	}
}

void	process_heredoc_input(char *delimiter, int heredoc_pipe, char **env)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_child_pid == 130)
		{
			free(line);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expand_string_if_needed_heredoc(&line, env);
		write(heredoc_pipe, line, ft_strlen(line));
		write(heredoc_pipe, "\n", 1);
		free(line);
	}
}

void	handle_heredoc_cmd(t_parsing *parsing, int i,
			t_env *env, int (**pipes)[2])
{
	int		heredoc_pipe[2];

	if (parsing[i].heredoc[parsing[0].countt.heredoc])
	{
		signal(SIGQUIT, SIG_IGN);
		while (parsing[i].heredoc[parsing[0].countt.heredoc])
		{
			if (pipe(heredoc_pipe) == -1)
			{
				perror("minishell: pipe");
				exit(EXIT_FAILURE);
			}
			signal(SIGINT, handler_heredoc_cmd);
			process_heredoc_input(parsing[i].heredoc[parsing[0].countt.heredoc],
				heredoc_pipe[1], env->env);
			signal(SIGINT, SIG_DFL);
			if (g_child_pid == 130)
			{
				free_all_heredoc(parsing, env, pipes);
				close(heredoc_pipe[0]);
				close(heredoc_pipe[1]);
				exit(130);
			}
			parsing[0].countt.heredoc++;
		}
		close(heredoc_pipe[1]);
		dup2(heredoc_pipe[0], STDIN_FILENO);
		close(heredoc_pipe[0]);
	}
}
