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

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_ptr {	
	char		result;
	int			(*func_ptr)(va_list ptr);
}	t_ptr;

int		handle_i(va_list ptr);
int		handle_s(va_list ptr);
int		handle_c(va_list ptr);
int		handle_d(va_list ptr);
int		handle_p(va_list ptr);
int		handle_u(va_list ptr);
int		handle_x(va_list ptr);
int		handle_upx(va_list ptr);
int		handle_pourcent(va_list ptr);
int		ft_putnbr_fd(int n, int fd);
int		ft_putchar_fd(char c, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_strlen(const char *String);
int		ft_putnbr_fd_base(unsigned long nb);
int		ft_putnbr_fd_unsigned(unsigned int n, int fd);
int		ft_putpourcent_fd(int fd);
int		ft_printf(const char *s, ...);
int		ft_putnbr_fd_baselow(unsigned int nb);
int		ft_putnbr_fd_baseup(unsigned int nb);
#endif