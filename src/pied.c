/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pied.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:05:49 by njaros            #+#    #+#             */
/*   Updated: 2023/01/12 08:35:26 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "labyrush.h"

void	do_nothing(void *rien)
{
	(void) rien;
}

void	gordon_freeman(void *class)
{
	t_class	*pouet;

	pouet = class;
	ft_lstclear(&pouet->elem, free);
	free(class);
}

void	freeteuse(void *to_free)
{
	char	**adr;
	int		i;

	adr = to_free;
	i = -1;
	while (adr[++i])
		free(adr[i]);
	free(to_free);
}

int	aff_vue_perso(char **maze, t_pos p, int lg, int ht, FILE *fd_log)
{
	char	**vision;
	char	toSend[31];
	int		x;
	int		y;

	ft_bzero(toSend, 31);
	y = 0;
	vision = malloc(sizeof(char *) * 6);
	vision[5] = NULL;
	while (y < 5)
	{
		vision[y] = malloc(6);
		if (!vision[y])
		{
			free_split(vision, y);
			return (0);
		}
		vision[y][5] = '\0';
		y++;
	}
	y = 0;
	while (y < 5)
	{
		x = 0;
		if (p.y - 2 + y < 0 || p.y - 2 + y >= ht)
			ft_strcpy(vision[y], "#####");
		while (x < 5 && (p.y - 2 + y >= 0) && (p.y - 2 + y < ht))
		{
			if (x == 2 && y == 2)
				vision[y][x] = 'P';
			else if (p.x - 2 + x < 0 || p.x - 2 + x >= lg)
				vision[y][x] = '#';
			else
				vision[y][x] = maze[p.y - 2 + y][p.x - 2 + x];
			x++;
		}
		y++;
	}
	y = -1;
	fprintf(fd_log, "Current vision : \n\n");
	while (++y < 5)
	{
		strcat(toSend, vision[y]);
		strcat(toSend, "\n");
		fprintf(fd_log, "%s\n", vision[y]);
		free(vision[y]);
	}
	if (write(1, toSend, 30) != 30)
	{
		fprintf(stderr, "buuuuuuug\n");
	}
	//fprintf(stderr, "subject : \n%s", toSend);
	free(vision);
	return (1);
}

void	aff_maze_debug(char **maze)
{
	int	j;

	fprintf(stderr, "\n");
	j = -1;
	while (maze[++j])
		fprintf(stderr, "%s", maze[j]);
	fprintf(stderr, "\n");
}

void	aff_maze(char **maze, FILE *fd_log)
{
	int	i;
	int	j;

	//ft_printf("\n");
	j = -1;
	while (maze[++j])
	{
		i = -1;
		while (maze[j][++i])
		{
			if (maze[j][i] == '%')
			{
				//ft_printf("💥");
				fprintf(fd_log, "💥");
			}
			else if (maze[j][i] == '#')
			{
				//ft_printf("🏰");
				fprintf(fd_log, "🏰");
			}
			else if (maze[j][i] == 'O')
			{
				//ft_printf("🥧");
				fprintf(fd_log, "🥧");
			}
			else if (maze[j][i] == 'E')
			{
				//ft_printf("🍽 ");
				fprintf(fd_log, "🍽");
			}
			else if (maze[j][i] == '.')
			{
				//ft_printf("🔲");
				fprintf(fd_log, "🔲");
			}
			else if (maze[j][i] == 'P')
			{
				//ft_printf("🚙");
				fprintf(fd_log, "🚙");
			}
			else
			{
				//ft_printf("%c", maze[j][i]);
				fprintf(fd_log, "%c", maze[j][i]);
			}
		}
		free(maze[j]);
	}
	free(maze);
}
