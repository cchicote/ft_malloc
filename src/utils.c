/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:22:31 by cchicote          #+#    #+#             */
/*   Updated: 2018/11/22 18:22:37 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		add_bucket_to_buckets(t_bucket **head, t_bucket *bucket)
{
	t_bucket *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = bucket;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = bucket;
}

void		add_chunk_to_chunks(t_chunk **head, t_chunk *chunk)
{
	t_chunk *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = chunk;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	chunk->next = NULL;
	tmp->next = chunk;
}

/*size_t			available(t_bucket *b)
{
	return (b->allocatable - b->allocated);
}*/

void		print_chunk_specs(t_chunk *chunk)
{
	printf("\e[35m\tChunk:\n\t\tSize: [%zu]\n\t\tAddress: [%p]\n\t\tFree?: [%s]\e[0m\n", chunk->size, chunk->mem, (chunk->is_free == TRUE ? "True" : "False"));

}

void		print_bucket_specs(t_bucket *bucket, int code)
{
	if (code == NEW)
		printf("\e[32mNew bucket:\n\tDimension: [%s]\n\tTotal size: [%zu]\n\tChunks allocated: [%d/100]\e[0m\n", (bucket->dimension == TINY ? "Tiny" : (bucket->dimension == SMALL ? "Small" : (bucket->dimension == LARGE ? "Large" : "Undefined"))), bucket->total_size, bucket->chunks_allocated);
	else if (code == RETRIEVED)
		printf("\e[33mRetrieved bucket:\n\tDimension: [%s]\n\tTotal size: [%zu]\n\tChunks allocated: [%d/100]\e[0m\n", (bucket->dimension == TINY ? "Tiny" : (bucket->dimension == SMALL ? "Small"  : (bucket->dimension == LARGE ? "Large" : "Undefined"))), bucket->total_size, bucket->chunks_allocated);
	else if (code == STANDARD)
		printf("\e[36mBucket:\n\tDimension: [%s]\n\tTotal size: [%zu]\n\tChunks allocated: [%d/100]\e[0m\n", (bucket->dimension == TINY ? "Tiny" : (bucket->dimension == SMALL ? "Small"  : (bucket->dimension == LARGE ? "Large" : "Undefined"))), bucket->total_size, bucket->chunks_allocated);
}
