/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:59:09 by njaros            #+#    #+#             */
/*   Updated: 2022/03/17 17:49:25 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

void	free_tabtab(int **to_free)
{
	int	i;

	i = -1;
	while (to_free[++i])
		free(to_free[i]);
	free(to_free);
}

t_list	*ft_lsttake(t_list **alst)
{
	t_list	*token;

	if (!*alst)
		return NULL;
	token = *alst;
	*alst = (*alst)->next;
	token->next = NULL;
	return (token);
}

noeud	*crea_noeud(int x, int y, noeud *parent, int **heuristiques)
{
	noeud	*new;

	new = malloc(sizeof(noeud));
	new->x = x;
	new->y = y;
	new->parent = parent;
	if (!parent)
	{
		new->val = heuristiques[y][x];
		new->cout = 0;
		return (new);
	}
	new->val = parent->cout + 1 + heuristiques[y][x];
	new->cout = parent->cout + 1;
	return (new);
}

void	closeddelete(t_list **closed, int x, int y)
{
	t_list	*first;
	t_list	*temp;
	noeud	*current;

	fprintf(stderr, "\ndel en cours \n");
	temp = NULL;
	first = *closed;
	current = (*closed)->content;
	while (current->x != x || current->y != y)
	{
		temp = *closed;
		*closed = (*closed)->next;
		current = (*closed)->content;
	}
	if (!temp)
	{
		temp = *closed;
		*closed = (*closed)->next;
		free(temp);
	}
	else
	{
		temp->next = (*closed)->next;
		free(*closed);
		*closed = first;
	}
	//fprintf(stderr, "\nfin del\n");
}

int	closed_val(t_list *closed, int x, int y)
{
	noeud	*current;

	while (closed)
	{
		current = closed->content;
		if (current->x == x && current->y == y)
			return (current->val);
		closed = closed->next;
	}
	return (-1);
}

void	check_noeud(int x, int y, t_list *open, t_list *closed, int **heuristiques, char **map)
{
	noeud	*new;
	int		val_closed;
	noeud	*current;

	current = open->content;
	if (map[y][x] != '#' && map[y][x] != '?')
	{
		val_closed = closed_val(closed, x, y);
		// fprintf(stderr, "valeur de val_closed et valeur noeud teste : %d et %d <- pos {%d, %d}\n", val_closed, heuristiques[y][x] + open->n->cout + 1, x, y);
		if (heuristiques[y][x] + current->cout + 1 < val_closed || val_closed == -1)
		{
			new = crea_noeud(x, y, current, heuristiques);
			ft_lstinsert_croissant(&open, ft_lstnew(new));
			if (val_closed != -1)
				closeddelete(&closed, x, y);
		//    fprintf(stderr, "%d %d\n", open->n->cout, open->next->n->cout);
		}
	}
}

int	a_star(char **map, int R, int C, int Kx, int Ky, int Tx, int Ty)
{
	int		**heuristiques;
	int		i = 0;
	int		j = 0;
	int		timer = 0;
	t_list	*open;
	t_list	*closed;
	noeud	*depart;
	noeud	*current_open;

	heuristiques = malloc(sizeof(int *) * R + 1);
	heuristiques[R] = NULL;
	open = NULL;
	closed = NULL;
	// creation des heuristiques des noeuds
	while (j < R)
	{
		heuristiques[j] = malloc(sizeof(int) * C);
		while (i < C)
		{
			if (map[j][i] == '#' || map[j][i] == '?')
				heuristiques[j][i] = -1;
			else
				heuristiques[j][i] = abs(Tx - i) + abs(Ty - j);
			i++;
		}
		i = 0;
		j++;
	}
	// heuristiques creees
	depart = crea_noeud(Kx, Ky, NULL, heuristiques);
	ft_lstadd_back(&open, ft_lstnew(depart));
	current_open = open->content;
	//creation open et closed de A*
	while (open && heuristiques[current_open->y][current_open->x] != 0)
	{
		i = current_open->x;
		j = current_open->y;
		// Recherche et creation des noeuds voisins + creation open et correction closed
		check_noeud(i + 1, j, open, closed, heuristiques, map);
		check_noeud(i - 1, j, open, closed, heuristiques, map);
		check_noeud(i, j + 1, open, closed, heuristiques, map);
		check_noeud(i, j - 1, open, closed, heuristiques, map);
		// fin de recherche et creation de noeuds voisins + open et delclosed
		ft_lstadd_back(&closed, ft_lsttake(&open)); //noeud lu va dans closed
		if (open)
			current_open = open->content;
		//fprintf(stderr, "heuristique nouvel open : %ld\n", heuristiques[open->n->y][open->n->x]);
	}
	i = Tx;
	j = Ty;
	ft_lstadd_back(&closed, ft_lsttake(&open));
	// open et closed creees
	// Creation du chemin a suivre
	noeud   *next_node;
	while (i != Kx || j != Ky)
	{
		next_node = search_parent(closed, i, j);
	//    fprintf(stderr, "coord parent trouve : {%d, %d}\n", next_node->x, next_node->y);
	//	fill_path(path, next_node->x - i, next_node->y - j);
		timer++;
		i = next_node->x;
		j = next_node->y;
	}
	fprintf(stderr, "\npathing memorise \n");
	// chemin a suivre cree
	// free des noeuds et open closed
	t_list  *temp;
	while (open)
	{
		free(open->content);
		temp = open;
		open = open->next;
		free(temp);
	}
	while (closed)
	{
		free(closed->content);
		temp = closed;
		closed = closed->next;
		free(temp);
	}
	free_tabtab(heuristiques);
	return (timer);
}