/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:49:26 by njaros            #+#    #+#             */
/*   Updated: 2023/01/06 12:09:28 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

int	err(int e, void *to_free)
{
	if (e == 1)
		fprintf(stderr, "erreur lors de la récupération ou la création du labyrinthe\n");
	if (e == 2)
	{
		fprintf(stderr, "erreur memoire affichage personnage\n");
		freeteuse(to_free);
	}
	if (e == 3)
		fprintf(stderr, "le ficher result.log ne s'est pas crée\n");
	return (e);
}

void	set_pos(t_pos *pers, t_pos *obj, char **maze)
{
	int	i;
	int	j;
	int	deux;

	deux = 0;
	j = -1;
	while (maze[++j] && deux < 2)
	{
		i = -1;
		while (maze[j][++i] && deux < 2)
		{
			if (maze[j][i] == 'O')
			{
				obj->y = j;
				obj->x = i;
				deux++;
			}
			if (maze[j][i] == 'E')
			{
				pers->y = j;
				pers->x = i;
				deux++;
			}
		}
	}
}

char	**recup_map(char *to_open, int *lg, int *ht, t_pos *pers, t_pos *obj)
{
	char	**maze;
	char	*line_read = NULL;
	int		fd;
	t_list	*lst = NULL;
	t_list	*secure;
	char	*retour_chariot_windows_check;

	fd = open(to_open, O_RDONLY);
	if (!fd)
	{
		fprintf(stderr, "entrée incorrecte\n");
		return (NULL);
	}
	lst = NULL;
	line_read = get_next_line(fd);
	while (line_read)
	{
		secure = ft_lstnew(line_read);
		if (!secure)
		{
			ft_lstclear(&lst, free);
			fprintf(stderr, "pas assez de memoire pour cette map\n");
			return (NULL);
		}
		ft_lstadd_back(&lst, secure);
		*ht += 1;
		line_read = get_next_line(fd);
	}
	close(fd);
	if (!lst)
		return (NULL);
	fd = -1;
	retour_chariot_windows_check = lst->content;
	*lg = ft_strlen(retour_chariot_windows_check) - 1;
	if (retour_chariot_windows_check[*lg - 1] == 13)
		*lg -= 1;
	maze = malloc(sizeof(char *) * (*ht + 1));
	maze[*ht] = NULL;
	secure = lst;
	while (lst)
	{
		maze[++fd] = lst->content;
		lst = lst->next;
	}
	while (secure)
	{
		lst = secure->next;
		free(secure);
		secure = lst;
	}
	set_pos(pers, obj, maze);
	return (maze);
}

int	ms(struct timeval t1, struct timeval t2)
{
	int	temps_ms;

	temps_ms = (t2.tv_sec - t1.tv_sec) * 1000;
	temps_ms += (t2.tv_usec - t1.tv_usec) / 1000;
	return (temps_ms);
}

long	us(struct timeval t1, struct timeval t2)
{
	long	temps_us;

	temps_us = (t2.tv_sec - t1.tv_sec) * 1000000;
	temps_us += (t2.tv_usec - t1.tv_usec);
	return (temps_us);
}

void	*timeout_handler(void *arg)
{
	time_handler	*tps;
	struct timeval	current;
	
	tps = arg;
	while (1)
	{
		gettimeofday(&current, NULL);
		pthread_mutex_lock(&(tps->mut));
		if (us(*(tps->t), current) > tps->timeout)
		{
			fprintf(tps->log, "\ntimeout...\n\n --DEFAITE-- \n\n");
			exit(0);
		}
		pthread_mutex_unlock(&(tps->mut));
		usleep(100);
	}
}

char **choose_mazer(int *lg, int *ht, t_pos *p, t_pos *o)
{
	int seed = reset_seed();
	switch (seed % 2)
	{
		case 1:
			return (mazer(lg, ht, p, o));
		default:
			return (mazer2(lg, ht, p, o));
	}
}

int	main(int ac, char **av)
{
	t_pos			perso;
	t_pos			objectif;
	int				lg = 0;
	int				ht = 0;
	int				timer;
	int				is_bot;
	int				victoire = 0;
	int				rip = 0;
	int				compteur = 0;
	char			**maze;
	char			*lulz_msg = NULL;
	char			lecture[50];
	pthread_t		timeout;
	struct timeval	last_input;
	struct timeval	begin;
	time_handler	th;
	long			astar_time;

	if (ac == 1)
		maze = choose_mazer(&lg, &ht, &perso, &objectif);
	else
		maze = recup_map(av[1], &lg, &ht, &perso, &objectif);
	if (!maze)
		return (err(1, NULL));
	int fd_log_create = open("result.log", O_CREAT | O_TRUNC, 0644);
	if (fd_log_create == -1)
		return (err(3, NULL));
	lecture[49] = '\0';
	
	fprintf(stderr, "maze done/parsed \n");

	aff_maze_debug(maze);
	
	is_bot = ask_if_is_bot();
	
	FILE *fd_log = fopen("result.log", "w");
	th.log = fd_log;
	ft_printf("width = %d high = %d begin_x = %d begin_y = %d\n", lg, ht, perso.x, perso.y);
	fprintf(fd_log, "width = %d high = %d begin_x = %d begin_y = %d\n", lg, ht, perso.x, perso.y);
	
	gettimeofday(&begin, NULL);
	
	timer = a_star(maze, ht, lg, perso.x, perso.y, objectif.x, objectif.y);

	gettimeofday(&last_input, NULL);

	astar_time = us(begin, last_input) * 2;
	
	fprintf(stderr, "a star done in time : %ld usec \n", us(begin, last_input));

	ft_printf("timer until O (goal) reached = %d\n", timer);
	fprintf(fd_log, "timer until O (goal) reached = %d\n\n", timer);
	
	if (is_bot)
	{
		gettimeofday(&last_input, NULL);
		begin.tv_sec = last_input.tv_sec;
		begin.tv_usec = last_input.tv_usec;
		th.t = &last_input;
		th.timeout = 20000;
		if (pthread_mutex_init(&(th.mut), NULL))
		{
			fprintf(stderr, "mutex init fail\n");
			return 1;
		}
		pthread_create(&timeout, NULL, timeout_handler, &th);
	}
	
	while (!victoire && !rip)
	{
		ft_bzero(lecture, 50);
		if (!aff_vue_perso(maze, perso, lg, ht, fd_log))
			return (err(2, maze));
		read(0, lecture, 50);
		if (is_bot)
		{
			pthread_mutex_lock(&(th.mut));
			gettimeofday(&last_input, NULL);
			if (th.timeout == astar_time)
				th.timeout = 20000;
			pthread_mutex_unlock(&(th.mut));
		}
		fprintf(fd_log, "\nsolver said : %s\n", lecture);
		compteur += keskiladi(maze, lecture, &perso, &timer, &victoire, &rip, &lulz_msg, &th, astar_time);
		if (compteur > 1000)
			rip = 1;
	}

	ft_printf("\n\n -----------BILAN---------- \n\n");
	fprintf(fd_log, "\n\n -----------BILAN---------- \n\n");
	
	aff_maze(maze, fd_log);
	if (victoire == 1)
	{
		ft_printf("\n\n--VICTOIRE--\n\n score : %d mouvements\n\n", compteur);
		fprintf(fd_log, "\n\n--VICTOIRE--\n\n score : %d mouvements\n\n", compteur);
		if (is_bot)
			fprintf(fd_log, "time to resolve : %ld usecs\n\n", us(last_input, begin));
	}
	if (victoire == 2)
	{
		ft_printf("\n\n--VICTOIRE--\n\n score : 0 mouvement\n\n");
		fprintf(fd_log, "\n\n--VICTOIRE--\n\n score : 0 mouvement\n\n");
	}
	if (rip)
	{
		ft_printf("\n\n%s\n\n--DEFAITE-- \n\n %d mouvements\n\n", lulz_msg, compteur);
		fprintf(fd_log, "\n\n%s\n\n--DEFAITE-- \n\n %d mouvements\n", lulz_msg, compteur);
	}
	if (lulz_msg)
		free(lulz_msg);
	pthread_cancel(timeout);
	pthread_detach(timeout);
	return (0);
}