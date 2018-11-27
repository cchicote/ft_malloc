/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:14:07 by cchicote          #+#    #+#             */
/*   Updated: 2018/11/07 16:14:15 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <errno.h>

t_chunk		*get_chunk(void *ptr)
{
	t_bucket	*tab[3] = {g_saved_data.tiny, g_saved_data.small, g_saved_data.large};
	t_bucket	*b;
	t_chunk		*c;
	int			i;

	i = 0;
	while (i < 3)
	{
		b = tab[i];
		while (b)
		{
			c = b->chunks;
			while (c)
			{
				if (c->mem == ptr)
					return (c);
				c = c->next;
			}
			b = b->next;
		}
		i++;
	}
	return (NULL);
}

void		ft_free(void *ptr)
{
	t_chunk *c;

	if (!ptr)
		return ;
	if (!(c = get_chunk(ptr)))
	{
		printf("WTF\n");
		return ;
	}
	if (munmap(c->mem, c->size) == -1)
		printf("ERROR: Value of errno: %d\n", errno); 
	c->is_free = TRUE;
}
