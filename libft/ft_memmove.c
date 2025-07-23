/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <rduport@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:10:41 by rduport           #+#    #+#             */
/*   Updated: 2024/11/20 14:49:04 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t size)
{
	char		*dest;
	const char	*src;
	size_t		i;

	if (!destination && !source)
		return (NULL);
	dest = (char *) destination;
	src = (const char *) source;
	if (dest > src)
		while (size--)
			dest[size] = src[size];
	else
	{
		i = 0;
		while (i < size)
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (destination);
}
