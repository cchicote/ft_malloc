/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:25:21 by cchicote          #+#    #+#             */
/*   Updated: 2018/12/13 16:25:32 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int                 is_chunk_in_bucket(t_bucket *bucket, void *ptr)
{
    size_t          i;

    i = 0;
    while (i < bucket->chunks)
    {
        if (bucket->chunks_tab[i].mem == ptr)
            return (TRUE);
        i++;
    }
    return (FALSE);
}

size_t              retrieve_chunk_index(t_bucket *bucket, void *ptr)
{
    size_t          i;

    i = 0;
    while (i < bucket->chunks)
    {
        if (bucket->chunks_tab[i].mem == ptr)
            return (i);
        i++;
    }
    return (0);
}

t_bucket            *retrieve_bucket(void *ptr)
{
    t_bucket	    *tab[3];
    t_bucket        *bucket;
    int             i;

    i = -1;
	tab[0] = g_saved_data.tiny;
	tab[1] = g_saved_data.small;
	tab[2] = g_saved_data.large;
    while (++i < 3)
    {
        bucket = tab[i];
        while (bucket)
        {
            if (is_chunk_in_bucket(bucket, ptr))
                return (bucket);
            bucket = bucket->next;
        }
    }
    return (NULL);
}

void                *realloc_chunk(void *ptr, size_t new_size)
{
    t_bucket        *bucket;
    void            *tmp;
    size_t          chunk_index;

    tmp = NULL;
    if (!(bucket = retrieve_bucket(ptr)))
        return (NULL);
    chunk_index = retrieve_chunk_index(bucket, ptr);
    if (new_size <= bucket->chunk_max_size)
    {
        bucket->chunks_tab[chunk_index].size = new_size;
        return (bucket->chunks_tab[chunk_index].mem);
    }
    else
    {
        tmp = malloc(new_size);
	    ft_memcpy(tmp, bucket->chunks_tab[chunk_index].mem,
            bucket->chunks_tab[chunk_index].size);
        free(ptr);
        return (tmp);
    }
    return (NULL);
}

void				*realloc(void *ptr, size_t size)
{
    if (!ptr)
        return (malloc(size));
    if (!size)
    {
        free(ptr);
        return (malloc(1));
    }
    return (realloc_chunk(ptr, size));
}