/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <rduport@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:53:09 by rduport           #+#    #+#             */
/*   Updated: 2024/11/15 15:38:32 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *source)
{
	int		i;
	char	*dup;

	i = 0;
	while (source[i])
		i++;
	dup = malloc((i + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (source[i])
	{
		dup[i] = source[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strdup_export(const char *source)
{
	int		i;
	char	*dup;

	if (ft_strncmp(source, "declare -x ", 11) == 0)
		return (ft_strdup(source));
	dup = ft_calloc(ft_strlen(source) + 12, sizeof(char));
	if (!dup)
		return (NULL);
	ft_strcpy(dup, "declare -x ");
	ft_strcat(dup, (char *)source);
	return (dup);
}

char	*ft_strdup_quote(const char *source)
{
	int		i;
	int		count;
	char	*dup;
	int		j;

	j = 0;
	i = -1;
	count = 0;
	while (source[++i])
		if (source[i] != '\'' && source[i] != '"')
			count++;
	dup = malloc((count + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (source[i])
	{
		if (source[i] != '\'' && source[i] != '"')
			dup[j++] = source[i];
		i++;
	}
	dup[j] = '\0';
	return (dup);
}
