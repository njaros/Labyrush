/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mazer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 08:40:28 by njaros            #+#    #+#             */
/*   Updated: 2022/03/19 14:00:35 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

char	**mazer(int *lg, int *ht, t_pos *perso, t_pos *objectif)
{
	struct timeval	t1;

	(void)perso;
	(void)objectif;
	gettimeofday(&t1, NULL);
	*lg = (t1.tv_usec % 11) + 10;
	*ht = ((t1.tv_usec << 1) % 11) + 10;
	return (NULL);
}