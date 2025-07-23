/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <rduport@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:44:58 by rduport           #+#    #+#             */
/*   Updated: 2024/11/19 17:27:46 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	const char	*memblock;
	size_t		i;

	i = 0;
	memblock = (const char *) memoryBlock;
	while (i < size)
	{
		if (memblock[i] == (const char)searchedChar)
			return ((void *)&memblock[i]);
		i++;
	}
	return (NULL);
}
