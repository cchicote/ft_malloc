/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:12:24 by cchicote          #+#    #+#             */
/*   Updated: 2018/11/07 16:12:26 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


t_chunk		*allocate_memory(void **b, size_t size)
{
	t_chunk		*chunk;
	t_bucket	*bucket;
	size_t		dimension;


	bucket = (t_bucket*)*b;
	dimension = (size_t)bucket->dimension == TINY ? TINY_MAX : SMALL_MAX;
	chunk = (t_chunk*)(*b + sizeof(t_bucket) + bucket->chunks_allocated * sizeof(t_chunk));
	chunk->size = size;
	chunk->is_free = FALSE;
	chunk->mem = (void*)(*b + bucket->offset + dimension * bucket->chunks_allocated);
	bucket->chunks_allocated++;
	chunk->next = NULL;
	add_chunk_to_chunks(&bucket->chunks, chunk);
	return (chunk);
}

t_chunk		*allocate_large_memory(void **b, size_t size)
{
	t_chunk		*chunk;
	t_bucket	*bucket;
	size_t		dimension;


	bucket = (t_bucket*)*b;
	dimension = (size_t)bucket->dimension == TINY ? TINY_MAX : SMALL_MAX;
	chunk = (t_chunk*)(*b + sizeof(t_bucket) + bucket->chunks_allocated * sizeof(t_chunk));
	chunk->size = size;
	chunk->is_free = FALSE;
	chunk->mem = (void*)(*b + bucket->offset + dimension * bucket->chunks_allocated);
	bucket->chunks_allocated++;
	chunk->next = NULL;
	add_chunk_to_chunks(&bucket->chunks, chunk);
	return (chunk);
}

void		*ft_malloc(size_t size)
{
	t_bucket *bucket;

	bucket = NULL;
	if (!size)
		return (NULL);
	if (size <= (size_t)TINY_MAX && !(bucket = retrieve_bucket(g_saved_data.tiny)))
		bucket = new_bucket(&(g_saved_data.tiny), TINY, TINY_MAX);
	else if (size > (size_t)TINY_MAX && size <= (size_t)SMALL_MAX && !(bucket = retrieve_bucket(g_saved_data.small)))
		bucket = new_bucket(&(g_saved_data.small), SMALL, SMALL_MAX);
	else if (size > (size_t)SMALL_MAX)
	{
		bucket = new_large_bucket(&(g_saved_data.large), LARGE, size);
		return (allocate_large_memory((void**)&bucket, size)->mem);
	}
	return (allocate_memory((void**)&bucket, size)->mem);
}
