/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:49:26 by njaros            #+#    #+#             */
/*   Updated: 2022/03/18 12:43:28 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

int	err(int e, void *to_free)
{
	if (e == 1)
		fprintf(stderr, "erreur lors de la récupération ou la création du labyrinthe\n");
	return (e);
}

void	set_pos(t_pos *pers, t_pos *obj, char **maze)
{

}

char	**recup_map(char *to_open, int *lg, int *ht, t_pos *pers, t_pos *obj)
{
	char	**maze;
	char	*line_read = NULL;
	int		fd;
	t_list	*lst = NULL;
	t_list	*secure;

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
		*ht++;
		line_read = get_next_line(fd);		
	}
	close(fd);
	if (!lst)
		return (NULL);
	fd = -1;
	*lg = ft_strlen((char *)lst->content);
	maze = malloc(sizeof(char *) * (*ht + 1));
	maze[*ht] = NULL;
	while (maze[++fd])
		maze[fd] = lst->content;
	ft_lstclear(lst, NULL);
	set_pos(pers, obj, maze);
	return (maze);
}

int	main(int ac, char **av)
{
	t_pos	perso;
	t_pos	objectif;
	int		lg = 0;
	int		ht = 0;
	int		timer;
	int		victoire = 0;
	int		rip = 0;
	int		compteur = 0;
	char	**maze;
	char	*lecture;

	if (ac == 1)
		maze = mazer(&lg, &ht, &perso, &objectif);
	else
		maze = recup_map(av[1], &lg, &ht, &perso, &objectif);
	if (!maze)
		return (err(1, NULL));
	printf("lg = %d\nht = %d\nperso_x = %d\nperso_y = %d\n", lg, ht, perso.x, perso.y);
	timer = a_star(maze, ht, lg, perso.x, perso.y, objectif.x, objectif.y);
	printf("compte a rebours une fois B atteint = %d\n", timer);
	while (timer >= 0 && !victoire && !rip)
	{
		aff_vue_perso(maze, perso);
		scanf("%s", lecture);
		compteur += keskiladi(maze, lecture, &perso, &objectif, &timer, &victoire, &rip);
	}
	aff_maze(maze);
	if (victoire)
		printf("pas dommage, vous n'avez pas perdu en ni plus ni moins %d coups\n", compteur);
	if (rip)
		printf("pas bravo, vous n'avez pas gagné en ni moins ni plus %d coups\n", compteur);
	return (0);
}