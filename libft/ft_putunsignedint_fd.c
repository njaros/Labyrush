/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsignedint_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:52:42 by njaros            #+#    #+#             */
/*   Updated: 2023/01/05 17:01:19 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsignedint_fd(unsigned int n, int fd)
{
	int	c;

	c = 0;
	if (n / 10 > 0)
	{
		c = c + ft_putunsignedint_fd((n / 10), fd);
		c = c + ft_putunsignedint_fd((n % 10), fd);
	}
	if (n / 10 == 0)
		c = c + ft_putchar_printf(n + '0', fd);
	return (c);
}
