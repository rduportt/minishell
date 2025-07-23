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

int	fill(int count, struct s_ptr *table, va_list ptr, const char *s)
{
	int	j;
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '%' && s[i + 1] != '\0')
		{
			j = -1;
			while (table[++j].result)
			{
				if (table[j].result == s[i + 1])
				{
					count += table[j].func_ptr(ptr);
					i++;
					break ;
				}
			}
			if (!table[j].result)
				count += ft_putchar_fd(s[i + 1], 1);
		}
		else
			count += ft_putchar_fd(s[i], 1);
	}
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int				i;
	va_list			ptr;
	int				count;
	struct s_ptr	table[10];

	if (!s)
		return (-1);
	table[0] = (t_ptr){'d', handle_d};
	table[1] = (t_ptr){'i', handle_i};
	table[2] = (t_ptr){'s', handle_s};
	table[3] = (t_ptr){'c', handle_c};
	table[4] = (t_ptr){'p', handle_p};
	table[5] = (t_ptr){'u', handle_u};
	table[6] = (t_ptr){'x', handle_x};
	table[7] = (t_ptr){'X', handle_upx};
	table[8] = (t_ptr){'%', handle_pourcent};
	table[9] = (t_ptr){0, NULL};
	i = 0;
	count = 0;
	va_start(ptr, s);
	count = fill(count, table, ptr, s);
	va_end(ptr);
	return (count);
}
