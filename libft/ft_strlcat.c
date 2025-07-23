/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <rduport@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:23:15 by rduport           #+#    #+#             */
/*   Updated: 2024/11/19 11:57:37 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check(char *dest, const char *src, size_t *len_dest, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = *len_dest;
	if (*len_dest < size - 1)
	{
		while (i < size - 1 && src[j] != '\0')
		{
			dest[i] = src[j];
			i++;
			j++;
		}
	}
	dest[i] = '\0';
}

size_t	ft_strlcat(char *dest, const char *src, int size)
{
	size_t	len_dest;
	size_t	len_src;

	len_dest = 0;
	len_src = 0;
	while (dest[len_dest] != '\0')
		len_dest++;
	while (src[len_src] != '\0')
		len_src++;
	if ((size_t)size <= len_dest)
		return (size + len_src);
	check(dest, src, &len_dest, size);
	return (len_dest + len_src);
}

//rajouter flag -lbsd
/*
#include <bsd/string.h>
#include <stdio.h>
int	main(void)
{
	const char	src[]="blabla";
	char	dest[50]="esa";
	char	dest2[50]="esa";
	size_t size=20;

	printf("%zu \n",strlcat(dest,src,size));
//renvoie longueur src + longueur initial dst
	printf("%s \n", dest);

	printf("%zu \n",ft_strlcat(dest2,src,size));
//renvoie longueur src + longueur initial dst
	printf("%s", dest2);
	
	return 0;
}*/
