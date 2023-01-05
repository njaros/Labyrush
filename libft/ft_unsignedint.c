/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsignedint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:23:04 by njaros            #+#    #+#             */
/*   Updated: 2023/01/05 17:01:57 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_unsignedint(unsigned int ap, char type)
{
	if (type == 'u')
		return (ft_putunsignedint_fd(ap, 1));
	else if (type == 'x')
		return (ft_puthexa_fd(ap, "0123456789abcdef", 1));
	else
		return (ft_puthexa_fd(ap, "0123456789ABCDEF", 1));
}
