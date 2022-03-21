/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mazer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 08:40:28 by njaros            #+#    #+#             */
/*   Updated: 2022/03/21 17:12:03 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

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

void	unir(t_class *a, t_list *b)
{
	t_class	*b_class;
	t_list	*a_lst;
	t_list	*b_lst;

	b_class = b->content;
	a_lst = a->elem;
	b_lst = b_class->elem;
	ft_lstadd_back(&a_lst, b_lst);
	free(b->content);
	b->content = NULL;
}

int	find(t_list *class_lst, int x, int y)
{
	t_class *current;
	t_list	*lst_elem;
	t_elem	*e;

	while (class_lst)
	{
		current = class_lst->content;
		lst_elem = current->elem;
		while (lst_elem)
		{
			e = lst_elem->content;
			if (x == e->x && y == e->y)
				return (current->num);
			lst_elem = lst_elem->next;
		}
		class_lst = class_lst->next;
	}
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
	fprintf(stderr, "%d | %d\n", lg, ht);
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
	t_elem	*e;
	while (class->elem)
	{
		e = class->elem->content;
		fprintf(stderr, "class num %d | singleton {%d,%d} \n", class->num, e->x, e->y);
		class->elem = class->elem->next;
	}
}

void	set_random(t_pos *perso, t_pos *objectif, int lg, int ht)
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
	}
}

char	**mazer(int *lg, int *ht, t_pos *perso, t_pos *objectif)
{
	char			**maze;
	struct timeval	t1;
	t_list			*lst_class;
	t_list			*first;

	lst_class = NULL;
	(void)perso;
	(void)objectif;
	gettimeofday(&t1, NULL);
	*lg = (t1.tv_usec % 21) + 10;
	*ht = ((t1.tv_usec << 1) % 21) + 10;
	if (*lg % 2 == 0)
		*lg += 1;
	if (*ht % 2 == 0)
		*ht += 1;
	maze = mazer_init(*lg, *ht, &lst_class);
	set_random(perso, objectif, *lg, *ht);
	first = lst_class;
	/*while (lst_class)
	{
		aff_class((t_class *)lst_class->content);
		lst_class = lst_class->next;
	}*/
	if (!maze)
		return (NULL);
	return (NULL);
}