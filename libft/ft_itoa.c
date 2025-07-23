/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <rduport@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:36:20 by raph              #+#    #+#             */
/*   Updated: 2024/11/20 14:43:34 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fill_itoa(char *itoa, int len, long buffer, int n)
{
	int	i;

	if (n == 0)
	{
		itoa[0] = '0';
		return ;
	}
	i = len;
	buffer = (long) n;
	if (n < 0)
	{
		itoa[0] = '-';
		buffer = -buffer;
	}
	while (buffer > 0)
	{
		i--;
		itoa[i] = ((buffer % 10) + '0');
		buffer /= 10;
	}
	itoa[len] = '\0';
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		len;
	long	buffer;

	buffer = (long) n;
	len = 0;
	if (n < 0)
	{
		len++;
		buffer = -buffer;
	}
	while (buffer > 0)
	{
		buffer /= 10;
		len++;
	}
	if (len == 0)
		len++;
	itoa = malloc((len + 1) * sizeof(char));
	if (itoa == NULL)
		return (NULL);
	fill_itoa(itoa, len, buffer, n);
	itoa[len] = '\0';
	return (itoa);
}
