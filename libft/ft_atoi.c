/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <rduport@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:47:15 by rduport           #+#    #+#             */
/*   Updated: 2024/11/19 15:13:53 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *string)
{
	int	i;
	int	signe;
	int	result;

	result = 0;
	signe = 1;
	i = 0;
	while ((string[i] >= 9 && string[i] <= 13) || string[i] == 32)
		i++;
	if (string[i] == '-')
	{
		signe = -1;
		i++;
	}
	if (string[i] == '+' && signe != -1)
		i++;
	while (string[i] >= '0' && string[i] <= '9')
		result = result * 10 + string[i++] - '0';
	if (result == 0)
		return (0);
	return (result * signe);
}
