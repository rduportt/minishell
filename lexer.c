/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:11:25 by rduport           #+#    #+#             */
/*   Updated: 2025/07/19 18:11:26 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char s1, char s2)
{
	if (s1 == '>' && s2 != '>')
		return (1);
	else if (s1 == '>' && s2 == '>')
		return (2);
	else if (s1 == '<' && s2 != '<')
		return (1);
	else if (s1 == '<' && s2 == '<')
		return (2);
	return (0);
}

void	check_redir(char **split, char const *s, t_lexer_count *count)
{
	if (s[count->i] == '<' || s[count->i] == '>')
	{
		if (count->buffer >= 0)
		{
			split[count->words++] = str_dup(s, count->buffer, count->i);
			count->buffer = -1;
		}
		count->buffer = count->i;
		count->i += is_redir(s[count->i], s[count->i + 1]);
		while (((s[count->i] >= 9 && s[count->i] <= 13)
				|| s[count->i] == 32) && s[count->i])
			count->i++;
	}
}

int	check_ft_lexer(char **split, t_token *lexer, int i)
{
	lexer[i].string = ft_strdup(split[i]);
	if (!lexer[i].string)
		return (0);
	if (split[i][0] == '>' && split[i][1] == '>')
		lexer[i].type = T_REDIR_APPEND;
	else if (split[i][0] == '<' && split[i][1] == '<')
		lexer[i].type = T_REDIR_HEREDOC;
	else if (split[i][0] == '<')
		lexer[i].type = T_REDIR_IN;
	else if (split[i][0] == '>')
		lexer[i].type = T_REDIR_OUT;
	else if (ft_strcmp(split[i], "|") == 0)
		lexer[i].type = T_PIPE;
	else
		lexer[i].type = T_WORD;
	return (1);
}

t_token	*ft_lexer(char **split)
{
	t_token			*lexer;
	int				i;
	int				quote_flag;

	if (!split)
		return (NULL);
	quote_flag = 0;
	i = 0;
	while (split[i])
		i++;
	lexer = malloc(sizeof(t_token) * (i + 1));
	if (!lexer)
		return (NULL);
	i = -1;
	while (split[++i])
		if (!check_ft_lexer(split, lexer, i))
			return (NULL);
	lexer[i].string = NULL;
	lexer[i].type = T_EOF;
	return (lexer);
}
