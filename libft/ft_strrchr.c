/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <rduport@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:24:52 by raph              #+#    #+#             */
/*   Updated: 2024/11/19 16:49:32 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searchedchar)
{
	char	*stringpointer;
	int		i;

	i = 0;
	stringpointer = NULL;
	while (string[i])
	{
		if (string[i] == (char) searchedchar)
			stringpointer = (char *)&string[i];
		i++;
	}
	if (string[i] == (char) searchedchar)
		stringpointer = (char *)&string[i];
	return (stringpointer);
}
