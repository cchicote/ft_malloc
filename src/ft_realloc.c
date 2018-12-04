/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:14:26 by cchicote          #+#    #+#             */
/*   Updated: 2018/11/07 16:14:32 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_chunk		*get_chunk(void *ptr, t_bucket *tab[3], t_bucket **bucket)
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
					*bucket = b;
					return (c);
				}
				c = c->next;
			}
			b = b->next;
		}
	}
	return (NULL);
}

void		*new_chunk(t_bucket *b, t_chunk *c, size_t size, void *data)
{
	void		*new_zone;

	if (!(new_zone = ft_malloc(size)))
		return (NULL);
	ft_memcpy(new_zone, data, c->size);
	free_chunk(b, c);
	return (new_zone);
}

void		*resize_chunk(t_bucket *b, t_chunk *c, size_t new_size)
{
	b->allocated = b->allocated - c->size - new_size;
	c->size = new_size;
	return (c->mem);
}

void		*ft_realloc(void *ptr, size_t size)
{
	t_bucket	*b;
	t_chunk		*c;
	t_bucket	*tab[3];

	tab[0] = g_saved_data.tiny;
	tab[1] = g_saved_data.small;
	tab[2] = g_saved_data.large;
	if (!ptr || !size || !(c = get_chunk(ptr, tab, &b)))
		return (NULL);
	if (size == c->size)
		return (ptr);
	else if (size < c->size && size >= b->chunk_min_size)
		return (resize_chunk(b, c, size));
	else if (size < c->size && size < b->chunk_min_size)
		return (new_chunk(b, c, size, ptr));
	else if (size > c->size)
	{
		if (size <= b->chunk_max_size &&
			b->allocated - c->size + size >= available(b) && c->next == NULL)
			return (resize_chunk(b, c, size));
		else
			return (new_chunk(b, c, size, ptr));
	}
	return (NULL);
}
