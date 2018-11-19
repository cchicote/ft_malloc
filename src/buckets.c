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
# define NEW 1
# define RETRIEVED 2

t_global 	g_saved_data;

void		print_bucket_specs(t_bucket *bucket, int code)
{
	if (code == NEW)
		printf("\e[32mNew bucket:\n\tDimension: [%s]\n\tAllocatable space total size: [%zu]\n\tBucket total size: [%zu]\n\tAllocated space: [%zu]\nAvailable space: [%zu]\e[0m\n", (bucket->dimension == TINY ? "Tiny" : (bucket->dimension == SMALL ? "Small" : "Large")), bucket->total_size, bucket->bucket_total_size, bucket->allocated, bucket->available);
	else if (code == RETRIEVED)
		printf("\e[33mRetrieved bucket:\n\tDimension: [%s]\n\tAllocatable space total size: [%zu]\n\tBucket total size: [%zu]\n\tAllocated space: [%zu]\nAvailable space: [%zu]\e[0m\n", (bucket->dimension == TINY ? "Tiny" : (bucket->dimension == SMALL ? "Small" : "Large")), bucket->total_size, bucket->bucket_total_size, bucket->allocated, bucket->available);

}

t_bucket	*retrieve_bucket(size_t size, t_bucket *head)
{
	t_bucket *tmp;

	tmp = head;
	while (tmp && size > tmp->available)
		tmp = tmp->next;
	if (tmp)
		print_bucket_specs(tmp, RETRIEVED);
	return (tmp);
}

void		push_to_end(t_bucket **head, t_bucket *elem)
{
	t_bucket *tmp;

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

t_bucket		*new_bucket(t_bucket **head, int dimension, size_t total_size)
{
	t_bucket *new;

	new = (t_bucket*)mmap(NULL, sizeof(t_bucket) + total_size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);	
	new->bucket_total_size = total_size + sizeof(t_bucket);
	new->total_size = total_size;
	new->available = total_size;
	new->allocated = 0;
	new->dimension = dimension;
	new->next = NULL;
	push_to_end(head, new);
	print_bucket_specs(new, NEW);
	return (new);
}
