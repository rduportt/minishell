/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:11:19 by rduport           #+#    #+#             */
/*   Updated: 2025/07/19 18:11:21 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quote(char const *s, t_lexer_count *count, char c)
{
	if (s[count->i] == '\"')
	{
		if (s[count->i] != c && s[count->i] != '|' && count->buffer < 0)
			count->buffer = count->i;
		count->i++;
		while (s[count->i] && s[count->i] != '\"')
			count->i++;
		if (!s[count->i])
			count->i--;
	}
	else if (s[count->i] == '\'')
	{
		if (s[count->i] != c && s[count->i] != '|' && count->buffer < 0)
			count->buffer = count->i;
		count->i++;
		while (s[count->i] && s[count->i] != '\'')
			count->i++;
		if (!s[count->i])
			count->i--;
	}
}

void	split_new_word(char **split, char const *s,
		t_lexer_count *count, char c)
{
	if (s[count->i] != c && s[count->i] != '|' && count->buffer < 0)
		count->buffer = count->i;
	else if ((s[count->i] == c || s[count->i] == '|') && count->buffer >= 0)
	{
		split[count->words++] = str_dup(s, count->buffer, count->i);
		if (s[count->i] == '|')
			split[count->words++] = str_dup(s, count->i, count->i + 1);
		count->buffer = -1;
	}
}

void	fill_split(char **split, char const *s, t_lexer_count *count, char c)
{
	while (s[++count->i])
	{
		if (s[count->i] == '|' && count->buffer < 0)
		{
			split[count->words++] = str_dup(s, count->i, count->i + 1);
			continue ;
		}
		check_redir(split, s, count);
		check_quote(s, count, c);
		split_new_word(split, s, count, c);
	}
	if (s[count->i] == '\0' && count->buffer >= 0)
		split[count->words++] = str_dup(s, count->buffer, count->i);
	split[count->words] = NULL;
}

char	**ft_split_readline(char const *s, char c)
{
	char			**split;
	t_lexer_count	count;

	if (!s)
		return (NULL);
	count.buffer = -1;
	split = split_alloc(s);
	if (split == NULL)
		return (NULL);
	count.i = -1;
	count.words = 0;
	fill_split(split, s, &count, c);
	return (split);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
