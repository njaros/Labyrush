/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labyrush.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:47:25 by njaros            #+#    #+#             */
/*   Updated: 2022/03/17 17:04:35 by njaros           ###   ########lyon.fr   */
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

typedef struct noeud
{
    int				x;
    int				y;
    int				val;
    int				cout;
    struct noeud	*parent;
}	noeud;

#endif
