/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:25:44 by cchicote          #+#    #+#             */
/*   Updated: 2018/12/13 16:25:54 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void                free_chunk(t_bucket *bucket, size_t i)
{
    bucket->chunks_tab[i].size = 0;
}

int                 retrieve_and_free_chunk(t_bucket *bucket, void *ptr)
{
    size_t          i;

    i = 0;
    while (i < bucket->chunks)
    {
        if (bucket->chunks_tab[i].mem == ptr)
        {
            free_chunk(bucket, i);
            return (TRUE);
        }
        i++;
    }
    return (FALSE);
}

void                retrieve_and_free_bucket(void *ptr)
{
    t_bucket	    *tab[3];
    t_bucket        *bucket;
    t_bucket        *previous;
    int             i;

    i = -1;
	tab[0] = g_saved_data.tiny;
	tab[1] = g_saved_data.small;
	tab[2] = g_saved_data.large;
    while (++i < 3)
    {
        bucket = tab[i];
        previous = NULL;
        while (bucket)
        {
            if (retrieve_and_free_chunk(bucket, ptr))
            {
                free_bucket(bucket, previous);
                return ;
            }
            previous = bucket;
            bucket = bucket->next;
        }
    }
    return ;
}

void                free_bucket(t_bucket *bucket, t_bucket *previous)
{
    size_t          i;

    i = 0;
    if (bucket == g_saved_data.tiny ||
        bucket == g_saved_data.small || bucket == g_saved_data.large)
        return ;
    while (i < bucket->chunks)
    {
        if (bucket->chunks_tab[i].size)
            return ;
        i++;
    }
    previous->next = bucket->next;
    munmap(bucket, bucket->size);
}

void				free(void *ptr)
{   
    if (!ptr)
        return ;
    retrieve_and_free_bucket(ptr);
    return ;
}