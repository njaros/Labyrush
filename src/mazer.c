/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mazer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 08:40:28 by njaros            #+#    #+#             */
/*   Updated: 2022/03/21 13:06:50 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

/*char	**init_mazer(int lg, int ht)
{
	char	**maze;
	int		i;
	int		j;
	int		

	i = 0;
	maze = malloc(sizeof(char *) * ht + 1);

}*/

char	**mazer(int *lg, int *ht, t_pos *perso, t_pos *objectif)
{
	//char			**maze;
	struct timeval	t1;

	(void)perso;
	(void)objectif;
	gettimeofday(&t1, NULL);
	*lg = (t1.tv_usec % 21) + 10;
	*ht = ((t1.tv_usec << 1) % 21) + 10;
	//maze = mazer_init(*lg, *ht);
	return (NULL);
}