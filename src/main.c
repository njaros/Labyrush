/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:49:26 by njaros            #+#    #+#             */
/*   Updated: 2022/03/17 14:20:06 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

int	main(void)
{
	struct timeval	t1;
	int				lg;
	int				ht;

	gettimeofday(&t1, NULL);
	lg = (t1.tv_usec % 11) + 10;
	ht = ((t1.tv_usec / 10) % 11) + 10;
	printf ("lg = %d | ht = %d\n", lg, ht);
	return (0);
}