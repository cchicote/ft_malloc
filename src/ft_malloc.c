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

	bucket = (t_bucket*)*b;
	chunk = (t_chunk*)(*b + bucket->allocated);
	bucket->allocated += sizeof(t_chunk) + size;
	chunk->size = size;
	chunk->is_free = FALSE;
	chunk->mem = (void*)((void*)chunk + sizeof(t_chunk));
	chunk->next = NULL;
	add_chunk_to_chunks(&bucket->chunks, chunk);
	return (chunk);
}

void		*ft_malloc(size_t size)
{
	t_bucket *bucket;
	t_chunk *ret;

	bucket = NULL;
	ret = NULL;
	if (!size)
		return (NULL);
	if (size <= (size_t)TINY_MAX && !(bucket = retrieve_bucket(size, g_saved_data.tiny)))
		bucket = new_bucket(&(g_saved_data.tiny), TINY, TINY_MAX);
	else if (size > (size_t)TINY_MAX && size <= (size_t)SMALL_MAX && !(bucket = retrieve_bucket(size, g_saved_data.small)))
		bucket = new_bucket(&(g_saved_data.small), SMALL, SMALL_MAX);
	else if (size > (size_t)SMALL_MAX)
		bucket = new_large_bucket(&(g_saved_data.large), LARGE, size);
	ret = allocate_memory((void**)&bucket, size);
	return (ret->mem);
}
