/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <rduport@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:34:49 by raph              #+#    #+#             */
/*   Updated: 2024/11/19 17:39:23 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length && (first[i] || second[i]))
	{
		if ((unsigned char)first[i] != (unsigned char)second[i])
			return (((unsigned char)first[i] - (unsigned char)second[i]));
		i++;
	}
	return (0);
}

int	ft_strncmp_export(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length && (first[i + 11] || second[i]))
	{
		if ((unsigned char)first[i + 11] != (unsigned char)second[i])
			return (((unsigned char)first[i + 11] - (unsigned char)second[i]));
		i++;
	}
	return (0);
}
