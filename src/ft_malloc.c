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

void		push_to_end2(t_chunk **head, t_chunk *elem)
{
	t_chunk *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = elem;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = elem;
}

t_chunk		*allocate_memory(void **bucket, size_t size)
{
	t_chunk 	*chunk;
	t_bucket	*b;

	b = (t_bucket*)*bucket;
	b->available -= size + sizeof(t_chunk);
	b->allocated += size + sizeof(t_chunk);
	chunk = (t_chunk*)(b + sizeof(t_bucket) + b->allocated);
	chunk->size = size;
	chunk->is_free = FALSE;
	chunk->mem = (void*)(chunk + sizeof(t_chunk));
	chunk->next = NULL;
	push_to_end2(&b->chunks, chunk);
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
		bucket = new_bucket(&(g_saved_data.tiny), TINY, TINY_MAX * 100);
	else if (size > (size_t)TINY_MAX && size <= (size_t)SMALL_MAX && !(bucket = retrieve_bucket(size, g_saved_data.small)))
		bucket = new_bucket(&(g_saved_data.small), SMALL, SMALL_MAX * 100);
	else if (size > (size_t)SMALL_MAX)
		bucket = new_bucket(&(g_saved_data.large), LARGE, size);
	ret = allocate_memory((void**)&bucket, size);
	return (ret->mem);
}
