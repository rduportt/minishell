/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <rduport@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:28:20 by raph              #+#    #+#             */
/*   Updated: 2024/11/20 15:00:46 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill_substr(size_t len, char const *s,
		unsigned int start, char *substr)
{
	unsigned int	i;
	size_t			j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i == start)
		{
			while (j < len && s[i])
			{
				substr[j] = s[i + j];
				j++;
			}
			substr[j] = '\0';
			return (substr);
		}
		i++;
	}
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(s);
	if (start >= i)
		return (ft_strdup(""));
	if (len > i - start)
		len = i - start;
	substr = malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	substr = fill_substr(len, s, start, substr);
	return (substr);
}
