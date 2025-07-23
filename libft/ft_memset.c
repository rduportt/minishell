/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <rduport@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:13:26 by rduport           #+#    #+#             */
/*   Updated: 2024/11/15 15:17:39 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*dest;
	int				i;

	dest = (unsigned char *) pointer;
	i = 0;
	while (count-- > 0)
		dest[i++] = value;
	return (dest);
}

/*#include <stdio.h>
#include <string.h>
int	main()
{
	int	array[] = {1,2,3,4,5,6,7,8,9};
	size_t size = sizeof(int) * 9;
	int	i;

	i = 0;
	while (i < 9)
	{
		printf("%d ", array[i]);
		i++;
	}
	printf("\n");

	ft_memset(array, 0, size);
	printf("ft_memset : \n");
	i = 0;
	while (i < 9)
	{
		printf("%d ", array[i]);
		i++;
	}
	printf("\n");

	memset(array, 0, size);
	printf("memset : \n");
	i = 0;
	while (i < 9)
	{
		printf("%d ", array[i]);
		i++;
	}
	printf("\n");
}*/
