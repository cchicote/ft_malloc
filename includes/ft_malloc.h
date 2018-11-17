/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:15:12 by cchicote          #+#    #+#             */
/*   Updated: 2018/11/07 16:15:14 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>

# define TRUE 1
# define FALSE 0

/*
** CODE DE DIMENSION DES ZONES
*/

# define TINY 1
# define SMALL 2
# define LARGE 3

/*
** TAILLE MAXIMALE DES ZONES
** N -> TINY
** M -> SMALL
*/

# define TINY_MAX (8 * getpagesize())
# define SMALL_MAX (32 * getpagesize())

typedef struct		s_zone
{
	int				type;
	size_t			size;
	struct s_zone	*next;
}					t_zone;

typedef struct		s_global
{
	t_zone			*tiny_head;
	t_zone			*small_head;
	t_zone			*large_head;
}					t_global;

extern t_global		g_saved_data;

/*
**			FT_MALLOC.C
*/
void				*ft_malloc(size_t size);

/*
**			FT_FREE.C
*/
void				ft_free(void *ptr);

/*
**			FT_REALLOC.C
*/
void				*ft_realloc(void *ptr, size_t size);

/*
**			ZONES.C
*/

t_zone				*new_zone(size_t size, int type);

#endif
