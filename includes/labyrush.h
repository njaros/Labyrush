/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labyrush.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:47:25 by njaros            #+#    #+#             */
/*   Updated: 2022/03/23 13:43:49 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LABYRUSH_H
# define LABYRUSH_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <math.h>
# include <fcntl.h>

// La structure ci-dessous aide un peu à la lisibilité du programme

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

// Les structure ci-dessous est celle utilisé pour l'algorithme union_find

typedef struct s_elem
{
	int	x;
	int	y;
}	t_elem;

typedef struct s_class
{
	int		num;
	t_list	*elem;
}	t_class;

// La structre ci-dessous est celle utilisé pour l'algorithme a*

typedef struct noeud
{
    int				x;
    int				y;
    int				val;
    int				cout;
    struct noeud	*parent;
}	noeud;

// Ptites fonctions utiles

void	free_tabtab(int **to_free);
void	freeteuse(void *to_free);
void	gordon_freeman(void *class);
void	aff_maze(char **maze);
void	aff_maze_debug(char **maze);

// Fonctions moins petites

int		aff_vue_perso(char **maze, t_pos p, int lg, int ht);
int		keskiladi(char **maze, char *lecture, t_pos *pers, int *timer, int *victoire, int *rip);
int		a_star(char **map, int row, int col, int xa, int ya, int xb, int yb);
char	**mazer(int *lg, int *ht, t_pos *perso, t_pos *objectif);

#endif
