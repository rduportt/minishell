/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:10:39 by rduport           #+#    #+#             */
/*   Updated: 2025/07/19 18:10:40 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc_no_cmd(t_parsing *parsing, int i)
{
	char	*line;

	while (parsing[i].heredoc[parsing[0].countt.heredoc])
	{
		signal(SIGINT, handler_heredoc);
		while (1)
		{
			line = readline("> ");
			if (g_child_pid == 130 || !line)
			{
				free(line);
				break ;
			}
			if (ft_strcmp(line,
					parsing[i].heredoc[parsing[0].countt.heredoc]) == 0)
			{
				free(line);
				break ;
			}
			free(line);
		}
		parsing[0].countt.heredoc++;
	}
}

void	handle_append_no_cmd(t_parsing *parsing, int i)
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
				parsing[0].exit_status = 1;
			}
			close(parsing[i].fd);
			parsing[0].countt.append++;
		}
	}
}

void	handle_infile_no_cmd(t_parsing *parsing, int i)
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
				parsing[0].exit_status = 1;
			}
			close(parsing[i].fd);
			parsing[0].countt.infile++;
		}
	}
}

void	handle_outile_no_cmd(t_parsing *parsing, int i)
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
				parsing[0].exit_status = 1;
			}
			close(parsing[i].fd);
			parsing[0].countt.outfile++;
		}
	}
}
