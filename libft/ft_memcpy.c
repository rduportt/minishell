/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <rduport@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:56:31 by rduport           #+#    #+#             */
/*   Updated: 2024/11/20 14:47:30 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	char		*dest;
	const char	*src;
	size_t		i;

	if (!destination && !source)
		return (NULL);
	dest = (char *)destination;
	src = (const char *)source;
	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	return (destination);
}
