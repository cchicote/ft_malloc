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

#include "malloc.h"

void			add_bucket_to_buckets(t_bucket **head, t_bucket *bucket)
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

void			add_chunk_to_chunks(t_chunk **head, t_chunk *chunk)
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

size_t			available(t_bucket *b)
{
	return (b->allocatable - b->allocated);
}
