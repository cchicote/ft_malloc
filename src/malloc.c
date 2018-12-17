/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:25:10 by cchicote          #+#    #+#             */
/*   Updated: 2018/12/13 16:25:16 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				*new_allocation(t_bucket *bucket, size_t size)
{
	size_t			i;

	i = 0;
	while (i < bucket->chunks)
	{
		if (!bucket->chunks_tab[i].size)
		{
			bucket->chunks_tab[i].size = size;
			return (bucket->chunks_tab[i].mem);
		}
		i++;
	}
	return (NULL);
}

void				*new_large_allocation(t_bucket *bucket, size_t size)
{
	if (!bucket->chunks_tab[0].size)
	{
		bucket->chunks_tab[0].size = size;
		return (bucket->chunks_tab[0].mem);
	}
	return (NULL);
}

void				*malloc(size_t size)
{
	t_bucket		*bucket;

	if (!size)
		return (NULL);
	if (size > SMALL)
	{
		bucket = new_large_bucket(&g_saved_data.large, size);
		return (new_large_allocation(bucket, size));
	}
	bucket = get_bucket(size);
	return (new_allocation(bucket, size));
}
