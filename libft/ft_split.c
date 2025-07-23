/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <rduport@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:27:15 by rduport           #+#    #+#             */
/*   Updated: 2024/11/26 14:18:31 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*str_dup(const char *src, int start, int i)
{
	char	*tab;
	int		index;

	index = 0;
	tab = (char *)malloc(sizeof(char) * (i - start) + 1);
	if (tab == NULL)
		return (NULL);
	while (start != i)
	{
		tab[index] = src[start];
		index++;
		start++;
	}
	tab[index] = '\0';
	return (tab);
}

static char	**split_alloc(const char *s, char c)
{
	int		i;
	int		buffer;
	int		words;
	char	**split;

	buffer = -1;
	words = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] != c && buffer < 0)
			buffer = i;
		else if (s[i] == c && buffer >= 0)
		{
			words++;
			buffer = -1;
		}
	}
	if (s[i] == '\0' && buffer >= 0)
		words++;
	words++;
	split = malloc(words * sizeof(char *));
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		words;
	int		buffer;

	buffer = -1;
	split = split_alloc(s, c);
	if (split == NULL)
		return (NULL);
	i = -1;
	words = 0;
	while (s[++i])
	{
		if (s[i] != c && buffer < 0)
			buffer = i;
		else if (s[i] == c && buffer >= 0)
		{
			split[words++] = str_dup(s, buffer, i);
			buffer = -1;
		}
	}
	if (s[i] == '\0' && buffer >= 0)
		split[words++] = str_dup(s, buffer, i);
	split[words] = NULL;
	return (split);
}
