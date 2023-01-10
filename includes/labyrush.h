/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labyrush.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:47:25 by njaros            #+#    #+#             */
/*   Updated: 2023/01/06 12:13:19 by njaros           ###   ########lyon.fr   */
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
# include <pthread.h>
# include <errno.h>
# include <string.h>

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

// La structure ci-sessous est utilisé pour la gestion du temps

typedef struct time_handler
{
	FILE 			*log;
	struct timeval	*t;
	long			timeout;
	pthread_mutex_t	mut;
}	time_handler;

// Ptites fonctions utiles

void	free_tabtab(int **to_free);
void	freeteuse(void *to_free);
void	gordon_freeman(void *class);
void	say_hello(int lg, int ht, int x, int y);
void	aff_maze(char **maze, FILE *fd_log);
void	aff_maze_debug(char **maze);
int		ask_if_is_bot();

// Fonctions moins petites

int		aff_vue_perso(char **maze, t_pos p, int lg, int ht, FILE *fd_log);
int		keskiladi(char **maze, char *lecture, t_pos *pers, int *timer, int *victoire, int *rip, char **msg, time_handler *th, long astar_timer);
int		a_star(char **map, int row, int col, int xa, int ya, int xb, int yb);

// Fonctions pour générateur de labyrhinte

char	**mazer2(int *lg, int *ht, t_pos *perso, t_pos *objectif);
char	**mazer(int *lg, int *ht, t_pos *perso, t_pos *objectif);
int		reset_seed(void);
void	clean_lst(t_list *lst);
void	unir(t_class *a, t_list *b, t_list **first);
int		find(t_list *class_lst, int x, int y);
t_class	*makeset(int n, t_elem *singleton);
t_elem	*new_elem(int x, int y);
t_list	*search_lst(int n, t_list *class);
t_class	*search_class(int n, t_list *class);

#endif
