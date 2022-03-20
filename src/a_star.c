/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:59:09 by njaros            #+#    #+#             */
/*   Updated: 2022/03/19 13:59:52 by njaros           ###   ########lyon.fr   */
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

void	ft_lstinsert_croissant(t_list **alst, t_list *new)
{
	t_list	*first;
	t_list	*temp;
	noeud	*current;
	noeud	*newn;
	int		new_val;

	newn = new->content;
	new_val = newn->val;
	first = *alst;
	temp = *alst;
	*alst = (*alst)->next;
	if (*alst)
		current = (*alst)->content;
	while ((*alst) && current->val < new_val)
	{
		temp = *alst;
		(*alst) = (*alst)->next;
		if (*alst)
			current = (*alst)->content;
	}
	if (!*alst)
	{
		temp->next = new;
		*alst = first;
	}
	else
	{
		temp->next = new;
		new->next = *alst;
		*alst = first;
	}
}

void	check_noeud(int x, int y, t_list *open, t_list *closed, int **heuristiques, char **map)
{
	noeud	*new;
	int		val_closed;
	noeud	*current;

	current = open->content;
	//fprintf(stderr, "x = %d, y = %d, cx = %d, cy = %d | map[y][x] = %c", x, y, current->x, current->y, map[y][x]);
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

noeud	*search_parent(t_list *closed, int x, int y)
{
	noeud	*current;

	while (closed)
	{
		current = closed->content;
		if (current->x == x && current->y == y)
			return (current->parent);
		closed = closed->next;
	}
	return (NULL);
}

int	a_star(char **map, int row, int col, int xa, int ya, int xb, int yb)
{
	int		**heuristiques;
	int		i = 0;
	int		j = 0;
	int		timer = 0;
	t_list	*open;
	t_list	*closed;
	noeud	*depart;
	noeud	*current;

	heuristiques = malloc(sizeof(int *) * row + 1);
	heuristiques[row] = NULL;
	open = NULL;
	closed = NULL;
	// creation des heuristiques des noeuds
	while (j < row)
	{
		heuristiques[j] = malloc(sizeof(int) * col);
		while (i < col)
		{
			if (map[j][i] == '#' || map[j][i] == '?')
				heuristiques[j][i] = -1;
			else
				heuristiques[j][i] = abs(xb - i) + abs(yb - j);
			i++;
		}
		i = 0;
		j++;
	}
	fprintf(stderr, "heuristiques creees\n");
	depart = crea_noeud(xa, ya, NULL, heuristiques);
	ft_lstadd_back(&open, ft_lstnew(depart));
	current = open->content;
	//creation open et closed de A*
	while (open && heuristiques[current->y][current->x] != 0)
	{
		i = current->x;
		j = current->y;
		// Recherche et creation des noeuds voisins + creation open et correction closed
		check_noeud(i + 1, j, open, closed, heuristiques, map);
		check_noeud(i - 1, j, open, closed, heuristiques, map);
		check_noeud(i, j + 1, open, closed, heuristiques, map);
		check_noeud(i, j - 1, open, closed, heuristiques, map);
		// fin de recherche et creation de noeuds voisins + open et delclosed
		ft_lstadd_back(&closed, ft_lsttake(&open)); //noeud lu va dans closed
		if (open)
			current = open->content;
		//fprintf(stderr, "heuristique nouvel open : %ld\n", heuristiques[open->n->y][open->n->x]);
	}
	fprintf(stderr, "listes faites\n");
	i = xb;
	j = yb;
	ft_lstadd_back(&closed, ft_lsttake(&open));
	// open et closed creees
	// Creation du chemin a suivre
	while (i != xa || j != ya)
	{
		current = search_parent(closed, i, j);
	//    fprintf(stderr, "coord parent trouve : {%d, %d}\n", next_node->x, next_node->y);
	//	fill_path(path, next_node->x - i, next_node->y - j);
		timer++;
		i = current->x;
		j = current->y;
	}
	//fprintf(stderr, "\npathing memorise \n");
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