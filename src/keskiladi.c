/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keskiladi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:28 by njaros            #+#    #+#             */
/*   Updated: 2022/03/19 14:06:35 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

char	*random_msg_cmd(char *str)
{
	struct timeval	t1;

	if (ft_strncmp(str, "Coucou\n", 8) == 0)
		return ("euh... coucou ? :D\n");
	if (ft_strncmp(str, "Ca va?\n", 8) == 0)
		return ("Ouiiiiiii ! Et toaaaaaa ?? <3\n");
	if (ft_strncmp(str, "Fait un truc\n", 14) == 0)
		return ("Hello World\n");
	gettimeofday(&t1, NULL);
	if (t1.tv_usec % 5 == 0)
		return ("Soudain, vous mourrez de décès\n");
	if (t1.tv_usec % 5 == 1)
		return ("Vous marchez sur un champignon invisible, explosif et toxique, pas de chance\n");
	if (t1.tv_usec % 5 == 2)
		return ("Vous avez attrapé le COVID, vous êtes confiné 2 semaines, cheh.\n");
	if (t1.tv_usec % 5 == 3)
		return ("Elden Ring vous appelle, vous décidez d'abandonner mon jeu stupide\n");
	return ("L'echo de votre commande retentit, vous vous rendez compte que vous vous êtes trompé\nVous vous suicidez de honte\nIl vous vous en faut peu...\n");
}

char	*random_msg_timer(void)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	if (t1.tv_usec % 5 == 0)
		return ("Trop tard, le petit pot de beurre que vous deviez apporter à mère-grand s'est périmé.\n");
	if (t1.tv_usec % 5 == 1)
		return ("En se sortant les doigts ça marche mieux!\n");
	if (t1.tv_usec % 5 == 2)
		return ("La montre fait *tic* *toc*... !!! NON PAS TICTOC !!!\nVous préfèrez mourir que de connaître la suite, tout le monde vous comprend\n");
	if (t1.tv_usec % 5 == 3)
		return ("zzzZZZzzz...\nZZz...\n\nz..?\n..!! Ah oui pardon, meurs !\nVoila\n\nzzz...\n");
	return ("Un petit pas pour l'homme, mais un pas de trop pour ce test\n");
}

char	*random_msg_wall(void)
{
	struct timeval	t1;
	
	gettimeofday(&t1, NULL);
	if (t1.tv_usec % 5 == 0)
		return ("On a oublié de vous dire que les murs sont électrisés. Oupsi\n");
	if (t1.tv_usec % 5 == 1)
		return ("Boire ou conduire, il faut boire\n");
	if (t1.tv_usec % 5 == 2)
		return ("Ce mur n'était pas comestible\n");
	if (t1.tv_usec % 5 == 3)
		return ("Seg faulted\n");
	return ("On est pas dans Wolfenstein 3D !\n");
}

int	bonne_commande(char *str)
{
	if (ft_strncmp(str, "DROITE\n", 8) == 0)
		return (1);
	if (ft_strncmp(str, "BAS\n", 5) == 0)
		return (2);
	if (ft_strncmp(str, "GAUCHE\n", 8) == 0)
		return (3);
	if (ft_strncmp(str, "HAUT\n", 6) == 0)
		return (4);
	return (0);
}

void	set_moove(int cmd, int *dx, int *dy)
{
	switch (cmd)
	{
		case 1:
			*dx = 1;
		case 2:
			*dy = 1;
		case 3:
			*dx = -1;
		case 4:
			*dy = -1;
	}
}

int	keskiladi(char **maze, char *lecture, t_pos *pers, int *timer, int *victoire, int *rip)
{
	int			cmd;
	static int	decompte = 0;
	int			dx = 0;
	int			dy = 0;

	cmd = bonne_commande(lecture);
	if (!cmd)
	{
		*rip = 1;
		printf("%s", random_msg_cmd(lecture));
		return (0);
	}
	if (decompte)
	{
		if (--(*timer) < 0)
		{
			*rip = 1;
			maze[pers->y][pers->x] = 'P';
			printf("%s", random_msg_timer());
			return (1);
		}
	}
	set_moove(cmd, &dx, &dy);
	if (maze[pers->y + dy][pers->x + dx] == '#')
	{
		*rip = 1;
		maze[pers->y][pers->x] = 'P';
		maze[pers->y + dy][pers->x + dx] = '%';
		printf("%s", random_msg_wall());
		return (1);
	}
	pers->x += dx;
	pers->y += dy;
	if (maze[pers->y][pers->x] == 'O' && !decompte)
		decompte = 1;
	if (maze[pers->y][pers->x] == 'E' && decompte)
		*victoire = 1;
	return (1);
}