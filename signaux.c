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
		if (g_child_pid == 0)
			rl_redisplay();
	}
}

void	handler_heredoc(int num)
{	
	if (num == SIGINT)
	{
		g_child_pid = 1;
		rl_done = 1;
		printf("\nMinishell>");
	}
}
