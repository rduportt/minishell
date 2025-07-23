/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <rduport@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:43:18 by raph              #+#    #+#             */
/*   Updated: 2024/11/20 14:44:04 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fill_strjoin(char *strjoin, char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		strjoin[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		strjoin[i + j] = s2[j];
		j++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*strjoin;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	len = i + j;
	strjoin = malloc((len + 1) * sizeof(char));
	if (strjoin == NULL)
		return (NULL);
	fill_strjoin(strjoin, s1, s2);
	strjoin[i + j] = '\0';
	return (strjoin);
}
