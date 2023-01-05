/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:04:58 by njaros            #+#    #+#             */
/*   Updated: 2023/01/05 17:01:44 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	recu_adr(unsigned long int nb, char *base, int fd)
{
	int		c;

	c = 0;
	if (nb / 16 > 0)
	{
		c = c + recu_adr(nb / 16, base, fd);
		c = c + recu_adr(nb % 16, base, fd);
	}
	if (nb / 16 == 0)
		c = c + ft_putchar_printf(base[nb], fd);
	return (c);
}

int	ft_putadr(unsigned long int adr, int fd)
{
	int		c;
	char	*base;

	c = 0;
	base = "0123456789abcdef";
	c = c + ft_putstr_printf("0x", fd);
	c = c + recu_adr(adr, base, fd);
	return (c);
}
