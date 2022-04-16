/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mazer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 08:40:28 by njaros            #+#    #+#             */
/*   Updated: 2022/03/23 16:25:06 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

int	reset_seed(void)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	return (t1.tv_usec);
}

void	clean_lst(t_list *lst)
{
	t_list	*temp;

	temp = NULL;
	while (lst)
	{
		if (!lst->content)
		{
			if (!temp)
			{
				temp = lst->next;
				free(lst);
				lst = temp;
				temp = NULL;
			}
			else
			{
				temp->next = lst->next;
				free(lst);
				lst = temp->next;
			}
		}
		else
		{
			temp = lst;
			lst = lst->next;
		}
	}
}

void	aff_lst_nbr(t_list *lst)
{
	t_class *current;
	t_elem	*e;

	current = lst->content;
	e = current->elem->content;
	fprintf(stderr,"aff_________ %d | %d\n", e->x, e->y);
}

void	unir(t_class *a, t_list *b, t_list **first)
{
	t_class	*b_class;
	t_list	*temp;

	temp = *first;
	b_class = b->content;
	ft_lstadd_back(&a->elem, b_class->elem);
	if (b == *first)
		*first = (*first)->next;
	else
	{
		while ((*first)->next != b)
			*first = (*first)->next;
		(*first)->next = b->next;
		*first = temp;
	}
	b->next = NULL;
	b_class->elem = NULL;
	ft_lstclear(&b, gordon_freeman);
}

int	find(t_list *class_lst, int x, int y)
{
	t_class *current;
	t_list	*ptr;
	t_elem	*e;

	//fprintf(stderr, "%d, %d\n", x, y);
	while (class_lst)
	{
		//fprintf(stderr, "check class content\n");
		current = class_lst->content;
		//fprintf(stderr, "check elem\n");
		ptr = current->elem;
		while (ptr)
		{
			//fprintf(stderr, "check elem content\n");
			e = ptr->content;
			if (x == e->x && y == e->y)
				return (current->num);
			//fprintf(stderr, "end check elem content\n");
			//fprintf(stderr, "end check elem\n");
			//fprintf(stderr, "check next elem\n");
			ptr = ptr->next;
		}
		class_lst = class_lst->next;
	}
	//fprintf(stderr, "end %d, %d\n", x, y);
	return (0);
}

t_class	*makeset(int n, t_elem *singleton)
{
	t_class	*new;

	new = malloc(sizeof(t_class));
	if (!new)
		return (NULL);
	new->num = n;
	new->elem = ft_lstnew(singleton);
	if (!new->elem)
	{
		free(singleton);
		return (NULL);
	}
	return (new);
}

t_elem	*new_elem(int x, int y)
{
	t_elem	*new;

	new = malloc(sizeof(t_elem));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	return (new);
}

char	**mazer_init(int lg, int ht, t_list **lst)
{
	char	**maze;
	int		x;
	int		y;
	int		i;
	int		swap_x;
	int		swap_y;
	t_elem	*secure_elem;
	t_class	*secure_class;
	t_list	*secure_lst;

	i = 0;
	//fprintf(stderr, "%d | %d\n", lg, ht);
	maze = malloc(sizeof(char *) * ht + 1);
	maze[ht] = NULL;
	if (!maze)
		return (NULL);
	swap_y = 0;
	y = -1;
	while (++y < ht)
	{
		maze[y] = malloc(lg + 2);
		if (!maze[y])
			return (free_split(maze, y));
		maze[y][lg] = '\n';
		maze[y][lg + 1] = '\0';
		swap_y = ft_switch(swap_y);
		x = -1;
		swap_x = 0;
		while (++x < lg)
		{
			swap_x = ft_switch(swap_x);
			if (swap_y || swap_x || x == lg - 1)
				maze[y][x] = '#';
			else
			{
				maze[y][x] = '.';
				secure_elem = new_elem(x, y);
				if (!secure_elem)
				{
					ft_lstclear(lst, gordon_freeman);
					free_split(maze, y);
					return (NULL);
				}
				secure_class = makeset(++i, secure_elem);
				if (!secure_class)
				{
					ft_lstclear(lst, gordon_freeman);
					free_split(maze, y);
					return (NULL);
				}
				secure_lst = ft_lstnew(secure_class);
				if (!secure_lst)
				{
					free(secure_elem);
					free(secure_class);
					ft_lstclear(lst, gordon_freeman);
					free_split(maze, y);
					return (NULL);
				}
				ft_lstadd_front(lst, secure_lst);
			}
		}
	}
	return (maze);
}

void	aff_class(t_class *class)
{
	t_list	*ptr;
	t_elem	*e;

	ptr = class->elem;
	while (ptr)
	{
		e = ptr->content;
		fprintf(stderr, "class num %d | singleton {%d,%d} \n", class->num, e->x, e->y);
		ptr = ptr->next;
	}
}

void	set_random(t_pos *perso, t_pos *objectif, int lg, int ht, t_pos *rand)
{
	struct timeval	t;
	int				val_x;
	int				val_y;

	perso->x = 0;
	perso->y = 0;
	objectif->x = 0;
	objectif->y = 0;
	val_x = lg / 2;
	val_y = ht / 2;
	while (perso->x == objectif->x && perso->y == objectif->y)
	{
		gettimeofday(&t, NULL);
		perso->x = 2 * (t.tv_usec % val_x) + 1;
		perso->y = 2 * (t.tv_usec % val_y) + 1;
		objectif->x = 2 * ((t.tv_usec << 1) % val_x) + 1;
		objectif->y = 2 * ((t.tv_usec << 1) % val_y) + 1;
		rand->x = 2 * ((t.tv_usec << 2) % val_x) + 1;
		rand->y = 2 * ((t.tv_usec << 2) % val_y) + 1;
	}
}

t_class	*search_class(int n, t_list *class)
{
	t_class	*current;

	while (class)
	{
		current = class->content;
		if (current->num == n)
			return (current);
		class = class->next;
	}
	return (NULL);
}

t_list	*search_lst(int n, t_list *class)
{
	t_class	*current;

	while (class)
	{
		current = class->content;
		if (current->num == n)
			return (class);
		class = class->next;
	}
	return (NULL);	
}

void	moove(t_pos *bal, char **maze, int dx, int dy, t_list **class)
{
	int		a;
	int		b;
	int		seed;
	t_class	*uni;
	t_list	*tmp;

	seed = reset_seed();
	a = find(*class, bal->x, bal->y);
	b = find(*class, bal->x + dx, bal->y + dy);
	if (!a || !b)
		fprintf(stderr, "\n!!!!!!_____!!!BUUUUUG!!!_____!!!!!_____!!!\n");
	if (a && b && a != b)
	{
		uni = search_class(a, *class);
		tmp = search_lst(b, *class);
		maze[bal->y + dy / 2][bal->x + dx / 2] = '.';
		unir(uni, tmp, class);
	}
	else if (a && b && maze[bal->y + dy / 2][bal->x + dx / 2] == '#' && !(seed % 7))
		maze[bal->y + dy / 2][bal->x + dx / 2] = '.';
	if (a && b)
	{
		bal->x += dx;
		bal->y += dy;
	}
}

int	rand_moove(t_pos *bal, int seed, t_list **class, char **maze, int ht, int lg)
{
	int		range = 0;
	int		rand;
	int		index = -1;
	char	dir = 0;

	if (bal->x + 2 < lg - 1 && ++range)
		dir |= 1; //0001
	if (bal->y + 2 < ht - 1 && ++range)
		dir |= 2; //0010
	if (bal->x - 2 > 0 && ++range)
		dir |= 4; //0100
	if (bal->y - 2 > 0 && ++range)
		dir |= 8; //1000
	if (seed / range == 0)
		seed = reset_seed();
	rand = seed % range + 1;
	while (++index < 4)
	{
		if (dir & (1 << index) && --rand != 0)
			dir -= (1 << index);
	}
	if (dir == 1)
		moove(bal, maze, 2, 0, class);
	if (dir == 2)
		moove(bal, maze, 0, 2, class);
	if (dir == 4)
		moove(bal, maze, -2, 0, class);
	if (dir == 8)
		moove(bal, maze, 0, -2, class);
	return (seed / range);
}

char	**mazer(int *lg, int *ht, t_pos *perso, t_pos *objectif)
{
	char			**maze;
	t_list			*lst_class;
	int				seed;
	t_pos			baladeur_rand; // un baladeur sur un point random
	t_pos			baladeur_p; // un baladeur sur perso
	t_pos			baladeur_o; // un baladeur sur objectif

	// L'idée est de faire se promener aléatoirement 3 électrons libre partant du personnage, de l'objectif et d'un endroit random.
	// A chaque déplacement, l'électron "décide" s'il casse un mur qu'il rencontre en se basant en grande partie sur l'algo Union_Find.
	// L'algo stoppe dès qu'un chemin est créé entre perso et objectif.
	
	lst_class = NULL;
	seed = reset_seed();
	*lg = (seed % 21) + 10;
	*ht = ((seed << 1) % 21) + 10;
	if (*lg % 2 == 0)
		*lg += 1;
	if (*ht % 2 == 0)
		*ht += 1;
	maze = mazer_init(*lg, *ht, &lst_class);
	if (!maze)
		return (NULL);
	set_random(perso, objectif, *lg, *ht, &baladeur_rand);
	baladeur_p = *perso;
	baladeur_o = *objectif;
	while (find(lst_class, perso->x, perso->y) != find(lst_class, objectif->x, objectif->y)
			|| find(lst_class, objectif->x, objectif->y) != find(lst_class, baladeur_rand.x, baladeur_rand.y))
	{
		seed = rand_moove(&baladeur_rand, seed, &lst_class, maze, *ht, *lg);
		seed = rand_moove(&baladeur_p, seed, &lst_class, maze, *ht, *lg);
		seed = rand_moove(&baladeur_o, seed, &lst_class, maze, *ht, *lg);
		//usleep(100000);
		//aff_maze_debug(maze);
	}
	maze[perso->y][perso->x] = 'E';
	maze[objectif->y][objectif->x] = 'O';
	//aff_maze_debug(maze);
	ft_lstclear(&lst_class, gordon_freeman);
	return (maze);
}