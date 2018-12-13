/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:26:01 by cchicote          #+#    #+#             */
/*   Updated: 2018/12/13 16:26:07 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int                 is_bucket_free(t_bucket *bucket)
{
    size_t          i;

    i = 0;
    while (i < bucket->chunks)
    {
        if (bucket->chunks_tab[i].size > 0)
            return (FALSE);
        i++;
    }
    return (TRUE);
}

void			    add_bucket_to_buckets(t_bucket **head, t_bucket *bucket)
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
