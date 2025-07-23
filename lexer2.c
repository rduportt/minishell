/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:11:12 by rduport           #+#    #+#             */
/*   Updated: 2025/07/19 18:11:13 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_dup(const char *src, int start, int i)
{
	char	*tab;
	int		index;

	index = 0;
	tab = (char *)malloc(sizeof(char) * (i - start) + 1);
	if (tab == NULL)
		return (NULL);
	while (start != i)
	{
		if (!src[start] || start == i)
			break ;
		tab[index] = src[start];
		index++;
		start++;
	}
	tab[index] = '\0';
	return (tab);
}

void	check_redir_alloc(const char *s, int *i, int *buffer, int *words)
{
	if (s[*i] == '<' || s[*i] == '>')
	{
		if (*buffer >= 0)
			*words += 1;
		*buffer = *i;
		*i += is_redir(s[*i], s[*i + 1]);
		while (((s[*i] >= 9 && s[*i] <= 13) || s[*i] == 32) && s[*i])
			*i += 1;
		*words += 1;
	}
}

void	check_quote_alloc(const char *s, int *i, int *buffer)
{
	if (s[*i] == '\"')
	{
		if (s[*i] != ' ' && s[*i] != '|' && *buffer < 0)
			*buffer = *i;
		*i += 1;
		while (s[*i] && s[*i] != '\"')
			*i += 1;
		if (!s[*i])
			*i -= 1;
	}
	else if (s[*i] == '\'')
	{
		if (s[*i] != ' ' && s[*i] != '|' && *buffer < 0)
			*buffer = *i;
		*i += 1;
		while (s[*i] && s[*i] != '\'')
			*i += 1;
		if (!s[*i])
			*i -= 1;
	}
}

void	split_new_word_alloc(const char *s, int *i, int *buffer, int *words)
{
	if (s[*i] != ' ' && s[*i] != '|' && *buffer < 0)
		*buffer = *i;
	else if ((s[*i] == ' ' || s[*i] == '|') && *buffer >= 0)
	{
		*words += 1;
		if (s[*i] == '|')
			*words += 1;
		*buffer = -1;
	}
}

char	**split_alloc(const char *s)
{
	int		i;
	int		buffer;
	int		words;
	char	**split;

	buffer = -1;
	words = 0;
	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == '|' && buffer < 0)
		{
			words++;
			continue ;
		}
		check_redir_alloc(s, &i, &buffer, &words);
		check_quote_alloc(s, &i, &buffer);
		split_new_word_alloc(s, &i, &buffer, &words);
	}
	if (s[i] == '\0' && buffer >= 0)
		words++;
	words++;
	split = malloc(words * sizeof(char *));
	return (split);
}
