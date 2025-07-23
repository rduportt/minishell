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

void	handle_heredoc_no_cmd(t_parsing *parsing, t_count count, int i)
{
	char	*line;

	while (parsing[i].heredoc[count.heredoc] && g_child_pid == 0)
	{
		signal(SIGINT, handler_heredoc);
		while (1)
		{
			line = readline("> ");
			if (g_child_pid == 1 || !line)
			{
				free(line);
				break ;
			}
			if (ft_strcmp(line, parsing[i].heredoc[count.heredoc]) == 0)
			{
				free(line);
				break ;
			}
			free(line);
		}
		count.heredoc++;
	}
}

void	handle_append_no_cmd(t_parsing *parsing, t_count count, int i)
{
	if (parsing[i].append[count.append])
	{
		while (parsing[i].append[count.append])
		{
			parsing[i].fd = open(parsing[i].append[count.append], O_WRONLY
					| O_CREAT | O_APPEND, 0644);
			if (parsing[i].fd == -1)
			{
				perror("minishell: open");
				parsing[0].exit_status = 1;
			}
			close(parsing[i].fd);
			count.append++;
		}
	}
}

void	handle_infile_no_cmd(t_parsing *parsing, t_count count, int i)
{
	if (parsing[i].infile[count.infile])
	{
		while (parsing[i].infile[count.infile])
		{
			parsing[i].fd = open(parsing[i].infile[count.infile], O_RDONLY);
			if (parsing[i].fd == -1)
			{
				perror("minishell: open");
				parsing[0].exit_status = 1;
			}
			close(parsing[i].fd);
			count.infile++;
		}
	}
}

void	handle_outile_no_cmd(t_parsing *parsing, t_count count, int i)
{
	if (parsing[i].outfile[count.outfile])
	{
		while (parsing[i].outfile[count.outfile])
		{
			parsing[i].fd = open(parsing[i].outfile[count.outfile], O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
			if (parsing[i].fd == -1)
			{
				perror("minishell: open");
				parsing[0].exit_status = 1;
			}
			close(parsing[i].fd);
			count.outfile++;
		}
	}
}
