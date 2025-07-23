/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <tirimesc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:21:25 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/25 13:21:28 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		num;

	num = 0;
	if (fd < 0)
		return (0);
	if (n == -2147483648)
	{
		write((int)fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		n = -n;
		write((int)fd, "-", 1);
		num += 1;
	}
	if (n >= 10)
		num += ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write((int)fd, &c, 1);
	return (num + 1);
}

int	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (fd < 0)
		return (0);
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putendl_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (fd < 0)
		return (0);
	while (s[i])
	{
		write ((int)fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
	return (i);
}

int	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return (0);
	write (fd, &c, 1);
	return (1);
}

int	ft_strlen(const char *String)
{
	int	i;

	i = 0;
	while (String[i])
		i++;
	return (i);
}
