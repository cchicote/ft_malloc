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

# define NEW 1
# define RETRIEVED 2
# define STANDARD 3

/*
** CODE DE DIMENSION DES ZONES
*/

# define TINY 1
# define SMALL 2
# define LARGE 3

/*
** TAILLE MAXIMALE DES CHUNKS
** N -> TINY
** M -> SMALL
*/

# define TINY_MAX (1 * getpagesize())
# define SMALL_MAX (8 * getpagesize())

typedef struct 		s_chunk
{
	size_t			size;
	int				is_free;
	void			*mem;
	struct s_chunk	*next;
}					t_chunk;

typedef struct		s_bucket
{
	size_t			allocated;
	size_t			allocatable;
	int				dimension;
	size_t			chunk_min_size;
	size_t			chunk_max_size;
	int				is_free;
	t_chunk			*chunks;
	//t_chunk			chunks[100];
	struct s_bucket	*next;
}					t_bucket;

typedef struct		s_global
{
	t_bucket		*tiny;
	t_bucket		*small;
	t_bucket		*large;
}					t_global;

extern t_global		g_saved_data;

/*
**					FT_MALLOC.C
*/
void				*ft_malloc(size_t size);
t_chunk				*find_free_chunk(t_bucket *b, size_t size);

/*
**					FT_FREE.C
*/
void				ft_free(void *ptr);
t_bucket			*get_bucket(void *ptr, t_bucket *tab[3]);
void				free_chunk(t_bucket *b, t_chunk *c);


/*
**					FT_REALLOC.C
*/
void				*ft_realloc(void *ptr, size_t size);

/*
**					BUCKETS.C
*/	
	
t_bucket			*new_bucket(t_bucket **head, int dimension, size_t chunk_size);
t_bucket			*retrieve_bucket(t_bucket *head, size_t size);
t_bucket			*new_large_bucket(t_bucket **head, int dimension, size_t chunk_size);
void				free_bucket(t_bucket *b);

/*
**					UTILS.C
*/
void				print_bucket_specs(t_bucket *bucket, int code);
void				print_chunk_specs(t_chunk *chunk);
size_t				available(t_bucket *b);
void				add_bucket_to_buckets(t_bucket **head, t_bucket *bucket);
void				add_chunk_to_chunks(t_chunk **head, t_chunk *chunk);

/*
**					SHOW_ALLOC_MEM.C
*/
void				show_alloc_mem(void);

#endif
