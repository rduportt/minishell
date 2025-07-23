/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:04:10 by rduport           #+#    #+#             */
/*   Updated: 2025/05/13 17:35:41 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	handler_sigint(int num)
{	
	if (num == SIGINT)
	{	
		write (STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_child_pid = 130;
	}
}

void	handler_heredoc(int num)
{	
	if (num == SIGINT)
	{
		g_child_pid = 130;
		rl_done = 1;
		printf("\nMinishell>");
	}
}

void	handler_heredoc_cmd(int sig)
{
	(void)sig;
	g_child_pid = 130;
	printf("\n");
	close(STDIN_FILENO);
}
