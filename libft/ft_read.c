/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:27:00 by njaros            #+#    #+#             */
/*   Updated: 2023/01/05 17:01:14 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_read(const char *fmt, va_list ap)
{
	int	i;
	int	c;

	c = 0;
	i = -1;
	while (fmt[++i])
	{
		if (fmt[i] == '%')
		{
			if (fmt[++i] == 'c' || fmt[i] == 'i' || fmt[i] == 'd')
				c = c + ft_int(va_arg(ap, int), fmt[i]);
			else if (fmt[i] == 's')
				c = c + ft_putstr_printf(va_arg(ap, char *), 1);
			else if (fmt[i] == 'u' || fmt[i] == 'x' || fmt[i] == 'X')
				c = c + ft_unsignedint(va_arg(ap, unsigned int), fmt[i]);
			else if (fmt[i] == 'p')
				c = c + ft_putadr(va_arg(ap, unsigned long int), 1);
			else
				c = c + ft_putchar_printf(fmt[i], 1);
		}
		else
			c = c + ft_putchar_printf(fmt[i], 1);
	}
	return (c);
}
