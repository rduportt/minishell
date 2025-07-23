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

int	handle_u(va_list ptr)
{
	int	i;

	i = ft_putnbr_fd_unsigned(va_arg(ptr, int), 1);
	return (i);
}

int	handle_x(va_list ptr)
{
	int	i;

	i = ft_putnbr_fd_baselow(va_arg(ptr, int));
	return (i);
}

int	handle_upx(va_list ptr)
{
	int	i;

	i = ft_putnbr_fd_baseup(va_arg(ptr, int));
	return (i);
}

int	handle_pourcent(va_list ptr)
{
	int	i;

	(void)ptr;
	i = ft_putpourcent_fd(1);
	return (i);
}
