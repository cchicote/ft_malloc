/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:14:55 by cchicote          #+#    #+#             */
/*   Updated: 2018/12/13 18:15:01 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				init_large_chunk(t_bucket *bucket)
{
	size_t			offset;
	void			*mem;

	bucket->chunks_tab[0].size = 0;
	mem = (void*)bucket + sizeof(t_bucket) + sizeof(t_chunk);
	offset = 16 - (size_t)mem % 16;
	offset = offset == 16 ? 0 : offset;
	bucket->chunks_tab[0].mem = mem + offset;
}

void				init_chunks(t_bucket *bucket, size_t chunk_max_size)
{
	size_t		i;
	size_t		offset;
	void		*mem;

	i = 0;
	while (i < bucket->chunks)
	{
		bucket->chunks_tab[i].size = 0;
		mem = (void*)bucket + sizeof(t_bucket) +
			sizeof(t_chunk) * bucket->chunks + i * chunk_max_size;
		offset = 16 - (size_t)mem % 16;
		offset = offset == 16 ? 0 : offset;
		bucket->chunks_tab[i].mem = mem + offset;
		i++;
	}
}

int					find_free_chunk(t_bucket *bucket)
{
	size_t			i;

	i = 0;
	while (i < bucket->chunks)
	{
		if (!bucket->chunks_tab[i].size)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

size_t				get_chunk_max_size(size_t size)
{
	if (size <= TINY)
		return (TINY);
	else
		return (SMALL);
}
