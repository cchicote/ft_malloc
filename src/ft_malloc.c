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

void		*ft_malloc(size_t size)
{
	t_bucket *bucket;

	bucket = NULL;
	if (!size)
		return (NULL);
	if (size <= (size_t)TINY_MAX && !(bucket = retrieve_bucket(size, g_saved_data.tiny)))
	{
		bucket = new_bucket(&(g_saved_data.tiny), TINY, TINY_MAX * 100);
	}
	else if (size <= (size_t)SMALL_MAX && !(bucket = retrieve_bucket(size, g_saved_data.small)))
	{
	}
	else if (size > (size_t)SMALL_MAX)
	{
	}
	allocate_memory(bucket, size);
	return ((void*)bucket);
}
