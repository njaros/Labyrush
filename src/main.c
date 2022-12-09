/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:49:26 by njaros            #+#    #+#             */
/*   Updated: 2022/12/08 18:48:03 by njaros           ###   ########lyon.fr   */
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

void	*timeout_handler(void *arg)
{
	int				timeout;
	struct timeval	*tps;
	struct timeval	current;
	long int		first;

	timeout = 50000;
	tps = arg;
	first = tps->tv_usec + tps->tv_sec * 1000000;
	while (1)
	{
		gettimeofday(&current, NULL);
		if (ms(*tps, current) > timeout)
		{
			printf("\ntimeout...\n\n --DEFAITE-- \n\n");
			exit(0);
		}
		if (timeout == 50000 && first != tps->tv_usec + tps->tv_sec * 1000000)
			timeout = 5000;
		usleep(1000);
	}
}

int	main(int ac, char **av)
{
	t_pos			perso;
	t_pos			objectif;
	int				lg = 0;
	int				ht = 0;
	int				timer;
	int				victoire = 0;
	int				rip = 0;
	int				compteur = 0;
	char			**maze;
	char			*lulz_msg = NULL;
	char			lecture[50];
	pthread_t		timeout;
	struct timeval	last_input;

	if (ac == 1)
		maze = mazer(&lg, &ht, &perso, &objectif);
	else
		maze = recup_map(av[1], &lg, &ht, &perso, &objectif);
	if (!maze)
		return (err(1, NULL));
	int fd_log_create = open("result.log", O_CREAT | O_TRUNC, 0644);
	if (fd_log_create == -1)
		return (err(3, NULL));
	lecture[49] = '\0';
	
	FILE *fd_log = fopen("result.log", "w");

	printf("lg = %d ht = %d perso_x = %d perso_y = %d\n", lg, ht, perso.x, perso.y);
	fprintf(fd_log, "lg = %d ht = %d perso_x = %d perso_y = %d\n", lg, ht, perso.x, perso.y);
	
	timer = a_star(maze, ht, lg, perso.x, perso.y, objectif.x, objectif.y);

	printf("compte a rebours une fois B atteint = %d\n", timer);
	fprintf(fd_log, "compte a rebours une fois B atteint = %d\n\n", timer);
	
	gettimeofday(&last_input, NULL);
	pthread_create(&timeout, NULL, timeout_handler, &last_input);
	
	while (!victoire && !rip)
	{
		if (!aff_vue_perso(maze, perso, lg, ht, fd_log))
			return (err(2, maze));
		fgets(lecture, 48, stdin);
		fprintf(fd_log, "\nsolver said : %s\n", lecture);
		compteur += keskiladi(maze, lecture, &perso, &timer, &victoire, &rip, &lulz_msg);
		gettimeofday(&last_input, NULL);
		if (compteur > 1000)
			rip = 1;
	}

	printf("\n\n -----------BILAN---------- \n\n");
	fprintf(fd_log, "\n\n -----------BILAN---------- \n\n");
	
	aff_maze(maze, fd_log);
	if (victoire == 1)
	{
		printf("\n\n--VICTOIRE--\n\n score : %d mouvements\n\n", compteur);
		fprintf(fd_log, "\n\n--VICTOIRE--\n\n score : %d mouvements\n\n", compteur);
	}
	if (victoire == 2)
	{
		printf("\n\n--VICTOIRE--\n\n score : 0 mouvement\n\n");
		fprintf(fd_log, "\n\n--VICTOIRE--\n\n score : 0 mouvement\n\n");
	}
	if (rip)
	{
		printf("\n\n%s\n\n--DEFAITE-- \n\n %d mouvements\n\n", lulz_msg, compteur);
		fprintf(fd_log, "\n\n%s\n\n--DEFAITE-- \n\n %d mouvements\n", lulz_msg, compteur);
	}
	if (lulz_msg)
		free(lulz_msg);
	pthread_cancel(timeout);
	pthread_detach(timeout);
	return (0);
}