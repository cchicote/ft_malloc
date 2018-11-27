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
#include <errno.h>

t_global 		g_saved_data;

t_bucket		*retrieve_bucket(t_bucket *head, size_t size)
{
	t_bucket *tmp;

	tmp = head;
	while (tmp && size > available(tmp))
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void			free_bucket(t_bucket *b)
{
	t_bucket *tmp;

	printf("On free le bucket\n");
	tmp = b->dimension == TINY ? g_saved_data.tiny : (b->dimension == SMALL ? g_saved_data.small : g_saved_data.large);
	while (tmp && tmp->next != b)
		tmp = tmp->next;
	tmp->next = b->next;
	if (munmap(b, b->allocatable) == -1)
		printf("ERROR: Value of errno: %d\n", errno); 
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
	new->allocatable = bucket_size;
	new->allocated = sizeof(t_bucket);
	add_bucket_to_buckets(head, new);
	return (new);
}

t_bucket		*new_large_bucket(t_bucket **head, int dimension, size_t chunk_size)
{
	t_bucket	*new;
	size_t		bucket_size;

	bucket_size = sizeof(t_bucket) + (sizeof(t_chunk) + chunk_size) * 100;
	bucket_size = (bucket_size / getpagesize() + 1) * getpagesize();

	new = (t_bucket*)mmap(NULL, bucket_size, 
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	new->dimension = dimension;
	new->allocatable = bucket_size;
	new->allocated = 0;
	add_bucket_to_buckets(head, new);
	return (new);
}
