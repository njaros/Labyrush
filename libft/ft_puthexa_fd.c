/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:10:13 by njaros            #+#    #+#             */
/*   Updated: 2023/01/05 17:02:08 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexa_fd(unsigned int nb, char *base, int fd)
{
	int	c;

	c = 0;
	if (nb / 16 > 0)
	{
		c = c + ft_puthexa_fd(nb / 16, base, fd);
		c = c + ft_puthexa_fd(nb % 16, base, fd);
	}
	if (nb / 16 == 0)
		c = c + ft_putchar_printf(base[nb], fd);
	return (c);
}
