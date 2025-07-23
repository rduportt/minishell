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

int	handle_i(va_list ptr)
{
	int	i;

	i = ft_putnbr_fd(va_arg(ptr, int), 1);
	return (i);
}

int	handle_s(va_list ptr)
{
	int		i;
	char	*res;

	i = 0;
	res = va_arg(ptr, char *);
	if (res)
		i = ft_putstr_fd(res, 1);
	else
		i = ft_putstr_fd("(null)", 1);
	return (i);
}

int	handle_c(va_list ptr)
{
	int	i;

	i = ft_putchar_fd((char)va_arg(ptr, int), 1);
	return (i);
}

int	handle_d(va_list ptr)
{
	int	i;

	i = ft_putnbr_fd(va_arg(ptr, int), 1);
	return (i);
}

int	handle_p(va_list ptr)
{
	int					i;
	unsigned long		res;

	res = va_arg(ptr, unsigned long);
	i = 2;
	if (!res)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	i += ft_putnbr_fd_base(res);
	return (i);
}
