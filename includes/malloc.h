/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:15:12 by cchicote          #+#    #+#             */
/*   Updated: 2018/11/07 16:15:14 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>

# define TRUE 1
# define FALSE 0

/*
** TAILLE MAXIMALE DES CHUNKS
** N -> TINY
** M -> SMALL
*/

# define TINY 256
# define SMALL 1024

typedef struct		s_chunk
{
	size_t			size;
	void			*mem;
}					t_chunk;

typedef struct		s_bucket
{
	size_t			chunk_max_size;
	size_t			size;
	struct s_bucket	*next;
	size_t			chunks;
	t_chunk			chunks_tab[];
}					t_bucket;

typedef struct		s_global
{
	t_bucket		*tiny;
	t_bucket		*small;
	t_bucket		*large;
}					t_global;

extern t_global		g_saved_data;

/*
**					MALLOC.C
*/
void				*malloc(size_t size);
void                *new_allocation(t_bucket *bucket, size_t size);
void                *new_large_allocation(t_bucket *bucket, size_t size);

/*
**					FREE.C
*/
void				free(void *ptr);
void                free_bucket(t_bucket *bucket, t_bucket *previous);
void                retrieve_and_free_bucket(void *ptr);
int                 retrieve_and_free_chunk(t_bucket *bucket, void *ptr);
void                free_chunk(t_bucket *bucket, size_t i);

/*
**					REALLOC.C
*/
void				*realloc(void *ptr, size_t size);
void              	*realloc_chunk(void *ptr, size_t new_size);
t_bucket            *retrieve_bucket(void *ptr);
size_t              retrieve_chunk_index(t_bucket *bucket, void *ptr);
int                 is_chunk_in_bucket(t_bucket *bucket, void *ptr);

/*
**					CALLOC.C
*/
void				*calloc(size_t count, size_t size);

/*
**					BUCKETS.C
*/
t_bucket			**get_correct_head(size_t size);
t_bucket			*new_bucket(t_bucket **head, size_t size);
t_bucket			*new_large_bucket(t_bucket **head, size_t size);
t_bucket			*find_free_space(t_bucket **head, size_t size);
t_bucket			*get_bucket(size_t size);

/*
**					CHUNKS.C
*/
void				init_chunks(t_bucket *bucket, size_t chunk_max_size);
void                init_large_chunk(t_bucket *bucket);
size_t         		get_chunk_max_size(size_t size);
int					find_free_chunk(t_bucket *bucket);

/*
**					UTILS.C
*/
void				add_bucket_to_buckets(t_bucket **head, t_bucket *bucket);
int                 is_bucket_free(t_bucket *bucket);

/*
**					SHOW_ALLOC_MEM.C
*/
void				show_alloc_mem(void);
void				print_address_hex(long num, int depth);
void				print_bucket_start(t_bucket *bucket, char *dim);
size_t				print_chunk_data(t_chunk c);
size_t				print_bucket(t_bucket *bucket, char *dim);

#endif
