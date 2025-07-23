/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:44:24 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/12 17:03:29 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putnbr_fd_base(unsigned long nb)
{
	char				*base ;
	int					num ;

	base = "0123456789abcdef";
	num = 0;
	if (nb >= 16)
		num = ft_putnbr_fd_base(nb / 16);
	write(1, &base[nb % 16], 1);
	return (num + 1);
}

int	ft_putnbr_fd_unsigned(unsigned int n, int fd)
{
	char	c;
	int		num;

	num = 0;
	if (fd < 0)
		return (0);
	if (n >= 10)
		num = ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write((int)fd, &c, 1);
	return (num + 1);
}

int	ft_putnbr_fd_baselow(unsigned int nb)
{
	char	*base ;
	int		num ;

	base = "0123456789abcdef";
	num = 0;
	if (nb >= 16)
		num = ft_putnbr_fd_baselow(nb / 16);
	write(1, &base[nb % 16], 1);
	return (num + 1);
}

int	ft_putnbr_fd_baseup(unsigned int nb)
{
	char	*base ;
	int		num ;

	base = "0123456789ABCDEF";
	num = 0;
	if (nb >= 16)
		num += ft_putnbr_fd_baseup(nb / 16);
	num++;
	write(1, &base[nb % 16], 1);
	return (num);
}

int	ft_putpourcent_fd(int nb)
{
	char	p;

	p = '%';
	write (nb, &p, 1);
	return (1);
}
