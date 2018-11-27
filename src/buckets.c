/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 20:03:15 by cchicote          #+#    #+#             */
/*   Updated: 2018/11/15 20:03:22 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_global 		g_saved_data;

t_bucket		*retrieve_bucket(t_bucket *head)
{
	t_bucket *tmp;

	tmp = head;
	while (tmp && tmp->chunks_allocated >= 100)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_bucket		*new_large_bucket(t_bucket **head, int dimension, size_t chunk_size)
{
	t_bucket	*new;
	size_t		bucket_size;

	bucket_size = sizeof(t_bucket) + (sizeof(t_chunk) + chunk_size);

	new = (t_bucket*)mmap(NULL, bucket_size, 
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	new->dimension = dimension;
	new->total_size = bucket_size;
	new->chunks_allocated = 0;
	new->offset = (bucket_size / getpagesize() - 100) * getpagesize();
	add_bucket_to_buckets(head, new);
	return (new);
}

t_bucket		*new_bucket(t_bucket **head, int dimension, size_t chunk_size)
{
	t_bucket	*new;
	size_t		bucket_size;


	bucket_size = sizeof(t_bucket) + (sizeof(t_chunk) + chunk_size) * 100;
	bucket_size = (bucket_size / getpagesize() + 1) * getpagesize();

	new = (t_bucket*)mmap(NULL, bucket_size, 
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	new->dimension = dimension;
	new->total_size = bucket_size;
	new->chunks_allocated = 0;
	new->offset = (bucket_size / getpagesize() - 100) * getpagesize();
	add_bucket_to_buckets(head, new);
	return (new);
}

