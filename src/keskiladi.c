/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keskiladi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:28 by njaros            #+#    #+#             */
/*   Updated: 2022/03/18 15:06:08 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

char	*random_msg_cmd(char *str)
{
	struct timeval	t1;

	if (ft_strncmp(str, "coucou\n", 6) == 0)
		return ("euh... coucou ? :D\n");
	gettimeofday(&t1, NULL);
	if (t1.tv_usec % 5 == 0)
		return ("Soudain, vous mourrez de décès\n");
	if (t1.tv_usec % 5 == 1)
		return ("Vous marchez sur un champignon invisible, explosif et toxique, pas de chance\n");
	if (t1.tv_usec % 5 == 2)
		return ("Vous avez attrapé le COVID, vous êtes confiné 2 semaines\n");
	if (t1.tv_usec % 5 == 3)
		return ("Elden Ring vous appelle, vous décidez d'abandonner mon jeu stupide\n");
	if (t1.tv_usec % 5 == 4)
		return ("L'echo de votre commande retentit, vous vous rendez compte que vous vous êtes trompé\nVous vous suicidez de honte\nIl vous vous en faut peu...\n");
}

int	keskiladi(char **maze, char *lecture, t_pos *pers, t_pos *obj, int *timer, int *victoire, int *rip)
{
	if (!bonne_commande(lecture))
	{
		printf("%s", random_msg_cmd(lecture));
		return (0);
	}

}