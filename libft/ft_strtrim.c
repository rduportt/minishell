/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <rduport@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:06:00 by raph              #+#    #+#             */
/*   Updated: 2024/11/20 14:44:36 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_max(int	*max, const char *s1, const char *set)
{
	int	len;
	int	j;

	len = 0;
	j = 0;
	while (set[j])
	{
		if (set[j] == s1[*max - 1])
		{
			len = len - 1;
			j = -1;
			*max = *max - 1;
		}
		j++;
	}
	return (len);
}

int	ft_start(int *i, int *j, char const *s1, char const *set)
{
	int	len;

	len = 0;
	while (set[*j])
	{
		if (set[*j] == s1[*i])
		{
			len = len - 1;
			*j = -1;
			*i = *i + 1;
		}
		*j = *j + 1;
	}
	return (len);
}

int	total_len(char const *s1, char const *set)
{
	int	len;
	int	i;
	int	j;
	int	max;

	j = 0;
	i = 0;
	len = 0;
	max = 0;
	while (s1[max])
		max++;
	len += ft_start(&i, &j, s1, set);
	len += ft_max(&max, s1, set);
	return (len);
}

int	fill_strtrim(char const *s1, char const *set, char *strtrim)
{
	int	i;
	int	j;
	int	len;
	int	max;

	max = 0;
	i = 0;
	j = 0;
	len = 0;
	while (s1[max])
		max++;
	ft_max(&max, s1, set);
	while (i < max)
	{
		while (set[j])
			ft_start(&i, &j, s1, set);
		strtrim[len] = s1[i];
		len++;
		i++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	int		len;
	int		i;

	i = 0;
	len = total_len(s1, set);
	while (s1[i])
		i++;
	len += i;
	if (len < 0)
		len = 0;
	strtrim = malloc((len + 1) * sizeof(char));
	if (strtrim == NULL)
		return (NULL);
	len = fill_strtrim(s1, set, strtrim);
	strtrim[len] = '\0';
	return (strtrim);
}
