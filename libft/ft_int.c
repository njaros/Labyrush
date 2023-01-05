/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:18:15 by njaros            #+#    #+#             */
/*   Updated: 2023/01/05 17:01:08 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_int(int ap, char type)
{
	if (type == 'c')
		return (ft_putchar_printf((char) ap, 1));
	else
		return (ft_putnbr_printf(ap, 1));
}
