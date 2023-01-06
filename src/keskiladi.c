/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keskiladi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:28 by njaros            #+#    #+#             */
/*   Updated: 2023/01/06 10:46:08 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

char	*random_msg_cmd(char *str)
{
	struct timeval	t1;
	int				rand;

	if (ft_strcmp(str, "Coucou\n") == 0)
		return ("euh... coucou ? :D\n");
	if (ft_strcmp(str, "Ca va?\n") == 0)
		return ("Ouiiiiiii ! Et toaaaaaa ?? <3\n");
	if (ft_strcmp(str, "Fait un truc\n") == 0)
		return ("Hello World\n");
	gettimeofday(&t1, NULL);
	rand = t1.tv_usec % 5;
	switch (rand)
	{
		case 0:
			return ("Soudain, vous mourrez de décès\n");
		case 1:
			return ("Vous marchez sur un champignon invisible, explosif et toxique, pas de chance\n");
		case 2:
			return ("Vous avez attrapé le COVID, vous êtes confiné 2 semaines, cheh.\n");
		case 3:
			return ("Elden Ring vous appelle, vous décidez d'abandonner mon jeu trop simple\n");
	}
	return ("L'echo de votre commande retentit, vous vous rendez compte que vous vous êtes trompé\nVous vous suicidez de honte\nIl vous vous en faut peu...\n");
}

char	*random_msg_timer(void)
{
	struct timeval	t1;
	int				rand;

	gettimeofday(&t1, NULL);
	rand = t1.tv_usec % 5;
	switch (rand)
	{
		case 0:
			return ("Trop tard, le petit pot de beurre que vous deviez apporter à mère-grand s'est périmé.\n");
		case 1:
			return ("En se sortant les doigts ça marche mieux!\n");
		case 2:
			return ("La montre fait *tic* *toc* *tic* *toc*... !!! NON PAS TICTOC !!!\nVous préfèrez mourir que de connaître la suite, tout le monde vous comprend\n");
		case 3:
			return ("zzzZZZzzz...\nZZz...\n\nz..?\n..!! Ah oui pardon, meurs !\nVoila\n\nzzz...\n");
	}
	return ("Un petit pas pour l'homme, mais un pas de trop pour ce test\n");
}

char	*random_msg_wall(void)
{
	struct timeval	t1;
	int				rand;
	
	gettimeofday(&t1, NULL);
	rand = t1.tv_usec % 5;
	switch (rand)
	{
		case 0:
			return ("On a oublié de vous dire que les murs sont électrisés. Oups!\n");
		case 1:
			return ("Boire ou conduire, il faut boire\n");
		case 2:
			return ("Ce mur n'était pas comestible\n");
		case 3:
			return ("Seg faulted\n");
	}
	return ("On est pas dans Wolfenstein 3D !\n");
}

int	bonne_commande(char *str)
{
	if (!ft_strncmp(str, "DROITE\n", 7) || !ft_strncmp(str, "RIGHT\n", 6))
		return (1);
	if (!ft_strncmp(str, "BAS\n", 4) || !ft_strncmp(str, "DOWN\n", 5))
		return (2);
	if (!ft_strncmp(str, "GAUCHE\n", 7) || !ft_strncmp(str, "LEFT\n", 5))
		return (3);
	if (!ft_strncmp(str, "HAUT\n", 5) || !ft_strncmp(str, "UP\n", 3))
		return (4);
	if (!ft_strcmp(str, "Je suis Chuck Norris\n"))
		return (5);
	return (0);
}

void	set_moove(int cmd, int *dx, int *dy)
{
	switch (cmd)
	{
		case 1:
			*dx = 1;
			break;
		case 2:
			*dy = 1;
			break;
		case 3:
			*dx = -1;
			break;
		case 4:
			*dy = -1;
			break;
	}
}

int	keskiladi(char **maze, char *lecture, t_pos *pers, int *timer, int *victoire, int *rip, char **msg, time_handler *th, long astar_timer)
{
	int			cmd;
	static int	decompte = 0;
	int			dx = 0;
	int			dy = 0;

	cmd = bonne_commande(lecture);
	if (!cmd)
	{
		*rip = 1;
		*msg = ft_strdup(random_msg_cmd(lecture));
		return (0);
	}
	if (cmd == 5)
	{
		*victoire = 2;
		return (0);
	}
	if (decompte && --(*timer) < 0)
	{
		*rip = 1;
		maze[pers->y][pers->x] = 'P';
		*msg = ft_strdup(random_msg_timer());
		return (1);
	}
	set_moove(cmd, &dx, &dy);
	if (maze[pers->y + dy][pers->x + dx] == '#')
	{
		*rip = 1;
		maze[pers->y][pers->x] = 'P';
		maze[pers->y + dy][pers->x + dx] = '%';
		*msg = ft_strdup(random_msg_wall());
		return (1);
	}
	pers->x += dx;
	pers->y += dy;
	if (maze[pers->y][pers->x] == 'O' && !decompte)
	{
		decompte = 1;
		pthread_mutex_lock(&(th->mut));
		th->timeout = astar_timer;
		pthread_mutex_unlock(&(th->mut));
	}
	if (maze[pers->y][pers->x] == 'E' && decompte)
		*victoire = 1;
	return (1);
}

int	ask_if_is_bot()
{
	char lecture[10];
	ft_printf("are you a bot ? (y/n)\n");
	read(0, lecture, 10);
	if (!ft_strncmp(lecture, "y\n", 2))
		return 1;
	if (!ft_strncmp(lecture, "n\n", 2))
		return 0;
	ft_printf("????\n");
	exit(0);
}