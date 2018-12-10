/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:14:07 by cchicote          #+#    #+#             */
/*   Updated: 2018/11/07 16:14:15 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			refragment_bucket(t_bucket *b)
{
	t_chunk		*c;

	c = b->chunks;
	while (c)
	{
		if (c->is_free && c->next && c->next->is_free &&
			c->size + sizeof(t_chunk) + c->next->size <= b->chunk_max_size)
		{
			c->size += sizeof(t_chunk) + c->next->size;
			c->next = c->next->next;
		}
		c = c->next;
	}
}

void			free_chunk(t_bucket *b, t_chunk *c)
{
	b->allocated -= c->size;
	c->is_free = TRUE;
	refragment_bucket(b);
}

t_bucket		*get_bucket(void *ptr, t_bucket *tab[3])
{
	t_bucket	*b;
	t_chunk		*c;
	int			i;

	i = -1;
	while (++i < 3)
	{
		b = tab[i];
		while (b)
		{
			c = b->chunks;
			while (c)
			{
				if (c->mem == ptr)
				{
					free_chunk(b, c);
					return (b);
				}
				c = c->next;
			}
			b = b->next;
		}
	}
	return (NULL);
}

int				is_bucket_to_free(t_bucket *b)
{
	t_chunk	*tmp;

	tmp = b->chunks;
	while (tmp)
	{
		if (!tmp->is_free)
			return (FALSE);
		tmp = tmp->next;
	}
	b->is_free = TRUE;
	if (b == g_saved_data.tiny || b == g_saved_data.small ||
		b == g_saved_data.large)
		return (FALSE);
	return (TRUE);
}

void			free(void *ptr)
{
	t_bucket	*b;
	t_bucket	*tab[3];

	tab[0] = g_saved_data.tiny;
	tab[1] = g_saved_data.small;
	tab[2] = g_saved_data.large;
	if (!ptr)
		return ;
	if (!(b = get_bucket(ptr, tab)))
		return ;
	if (is_bucket_to_free(b))
		free_bucket(b);
}
