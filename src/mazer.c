/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mazer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 08:40:28 by njaros            #+#    #+#             */
/*   Updated: 2022/03/21 15:33:03 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

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
					return (NULL);
				}
				secure_class = makeset(++i, secure_elem);
				if (!secure_class)
				{
					ft_lstclear(lst, gordon_freeman);
					return (NULL);
				}
				secure_lst = ft_lstnew(secure_class);
				if (!secure_class)
					{
						free(secure_elem);
						free(secure_class);
						ft_lstclear(lst, gordon_freeman);
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
	first = lst_class;
	while (lst_class)
	{
		aff_class((t_class *)lst_class->content);
		lst_class = lst_class->next;
	}
	if (!maze)
		return (NULL);
	return (NULL);
}