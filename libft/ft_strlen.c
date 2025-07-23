/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <rduport@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:38:20 by raph              #+#    #+#             */
/*   Updated: 2024/11/15 15:33:48 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

size_t	ft_strlen_char(const char *string, char c)
{
	size_t	i;

	i = 0;
	while (string[i] && string[i] != c)
		i++;
	return (i);
}
