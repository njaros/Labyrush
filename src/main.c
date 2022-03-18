/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:49:26 by njaros            #+#    #+#             */
/*   Updated: 2022/03/18 09:01:29 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

int	err(int e, void *to_free)
{
	if (e == 1)
		fprintf(stderr, "erreur lors de la récupération ou la création du labyrinthe\n");
	return (e);
}

int	main(int ac, char **av)
{
	t_pos	perso;
	t_pos	objectif;
	int		lg;
	int		ht;
	char	**maze;

	if (ac == 1)
		maze = mazer(&lg, &ht, &perso, &objectif);
	else
		maze = recup_map(av[1], &lg, &ht, &perso, &objectif);
	if (!maze)
		return (err(1, NULL));
	printf("lg = %d | ht = %d | perso_x = %d | perso_y = %d", lg, ht, perso.x, perso.y);
	printf(" | compte a rebours une fois B atteint = %d\n", a_star(maze, ht, lg, perso.x, perso.y, objectif.x, objectif.y));
	while (1)
	{
		
	}
	return (0);
}