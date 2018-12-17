/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buckets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:02:11 by cchicote          #+#    #+#             */
/*   Updated: 2018/12/13 17:02:16 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_global			g_saved_data;

t_bucket			**get_correct_head(size_t size)
{
	if (size <= TINY)
		return (&g_saved_data.tiny);
	else
		return (&g_saved_data.small);
}

t_bucket			*new_bucket(t_bucket **head, size_t size)
{
	t_bucket		*new;
	size_t			bucket_size;
	size_t			chunk_max_size;
	size_t			chunk_total_size;

	chunk_max_size = get_chunk_max_size(size);
	chunk_total_size = chunk_max_size + sizeof(t_chunk) + 16;
	bucket_size = sizeof(t_bucket) + 100 * chunk_total_size;
	bucket_size = (bucket_size / getpagesize() + 1) * getpagesize();
	new = (t_bucket*)mmap(NULL, bucket_size,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!new)
		return (NULL);
	new->size = bucket_size;
	new->chunk_max_size = chunk_max_size;
	new->chunks = (bucket_size - sizeof(t_bucket)) / chunk_total_size;
	init_chunks(new, chunk_max_size);
	new->next = NULL;
	add_bucket_to_buckets(head, new);
	return (new);
}

t_bucket			*new_large_bucket(t_bucket **head, size_t size)
{
	t_bucket		*new;
	size_t			bucket_size;
	size_t			chunk_total_size;

	chunk_total_size = size + sizeof(t_chunk) + 16;
	bucket_size = sizeof(t_bucket) + chunk_total_size;
	bucket_size = (bucket_size / getpagesize() + 1) * getpagesize();
	new = (t_bucket*)mmap(NULL, bucket_size,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!new)
		return (NULL);
	new->size = bucket_size;
	new->chunk_max_size = size;
	new->chunks = 1;
	init_large_chunk(new);
	new->next = NULL;
	add_bucket_to_buckets(head, new);
	return (new);
}

t_bucket			*find_free_space(t_bucket **head, size_t size)
{
	t_bucket		*tmp;

	tmp = *head;
	while (tmp)
	{
		if (find_free_chunk(tmp))
			return (tmp);
		tmp = tmp->next;
	}
	return (new_bucket(head, size));
}

t_bucket			*get_bucket(size_t size)
{
	t_bucket		**head;

	head = get_correct_head(size);
	return (find_free_space(head, size));
}
