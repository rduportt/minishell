/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <rduport@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:54:17 by raph              #+#    #+#             */
/*   Updated: 2024/11/19 12:21:15 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int searchedchar)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == (char) searchedchar)
			return ((char *)&string[i]);
		i++;
	}
	if (string[i] == (char) searchedchar)
		return ((char *)&string[i]);
	return (NULL);
}
