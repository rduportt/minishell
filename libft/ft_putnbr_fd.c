/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <rduport@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:39:50 by rduport           #+#    #+#             */
/*   Updated: 2024/11/29 14:00:22 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	nbneg(int *nb, int fd)
{
	if (*nb < 0)
	{
		write(fd, "-", 1);
		*nb = -*nb;
	}
}

void	ft_putnbr_fd(int nb, int fd)
{
	char	buffer[10];
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (nb == 0)
		write(fd, "0", 1);
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	nbneg(&nb, fd);
	while (nb != 0)
	{
		buffer[i] = nb % 10 + '0';
		nb /= 10;
		i++;
	}
	while (--i >= 0)
		write(fd, &buffer[i], 1);
}
