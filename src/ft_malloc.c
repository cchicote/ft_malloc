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

t_chunk		*find_free_chunk(t_bucket *b, size_t size)
{
	t_chunk *tmp;

	tmp = b->chunks;
	while (tmp)
	{
		if (tmp->size == size && tmp->is_free)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_chunk		*allocate_memory(void **b, size_t size)
{
	t_chunk		*chunk;
	t_bucket	*bucket;

	bucket = (t_bucket*)*b;
	if ((chunk = find_free_chunk(bucket, size)))
	{
		bucket->allocated += sizeof(t_chunk) + size;
		return (chunk);
	}
	chunk = (t_chunk*)(*b + bucket->allocated);
	chunk->size = size;
	chunk->is_free = FALSE;
	chunk->mem = (void*)(*b + bucket->allocated + sizeof(t_chunk));
	bucket->allocated += sizeof(t_chunk) + size;
	bucket->is_free = FALSE;
	chunk->next = NULL;
	add_chunk_to_chunks(&bucket->chunks, chunk);
	return (chunk);
}

t_chunk		*allocate_large_memory(void **b, size_t size)
{
	t_chunk		*chunk;
	t_bucket	*bucket;

	bucket = (t_bucket*)*b;
	if ((chunk = find_free_chunk(bucket, size)))
	{
		bucket->allocated += sizeof(t_chunk) + size;
		return (chunk);
	}
	chunk = (t_chunk*)(*b + bucket->allocated);
	chunk->size = size;
	chunk->is_free = FALSE;
	chunk->mem = (void*)(*b + bucket->allocated + sizeof(t_chunk));
	bucket->allocated += sizeof(t_chunk) + size;
	bucket->is_free = FALSE;
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
	if (size <= (size_t)TINY_MAX && !(bucket = retrieve_bucket(g_saved_data.tiny, size)))
		bucket = new_bucket(&(g_saved_data.tiny), TINY, TINY_MAX);
	else if (size > (size_t)TINY_MAX && size <= (size_t)SMALL_MAX && !(bucket = retrieve_bucket(g_saved_data.small, size)))
		bucket = new_bucket(&(g_saved_data.small), SMALL, SMALL_MAX);
	else if (size > (size_t)SMALL_MAX)
	{
		bucket = new_large_bucket(&(g_saved_data.large), LARGE, size);
		return (allocate_large_memory((void**)&bucket, size)->mem);
	}
	return (allocate_memory((void**)&bucket, size)->mem);
}
