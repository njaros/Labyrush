/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pied.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:05:49 by njaros            #+#    #+#             */
/*   Updated: 2022/03/18 13:40:07 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

void	aff_vue_perso(char **maze, t_pos p, int lg, int ht)
{
	char	**vision;
	int		x;
	int		y;

	y = 0;
	vision = malloc(sizeof(char *) * 5);
	while (y < 5)
	{
		vision[y] = malloc(6);
		vision[y][5] = '\0';
	}
	y = 0;
	while (y < 5)
	{
		x = 0;
		if (p.y - 2 + y < 0 || p.y - 2 + y > ht)
			ft_strcpy(vision[y], "?????");
		while (x < 5 && (p.y - 2 + y >= 0) && (p.y - 2 + y <= ht))
		{
			if (x == 2 && y == 2)
				vision[y][x] = 'P';
			else if (p.x - 2 + x < 0 || p.x - 2 + x)
				vision[y][x] = '?';
			else if ()
			{
				
			}
			
			x++;
		}
		y++;
	}
}