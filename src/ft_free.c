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

t_bucket		*get_bucket(void *ptr)
{
	t_bucket	*tab[3] = {g_saved_data.tiny, g_saved_data.small, g_saved_data.large};
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
					b->allocated -= c->size - sizeof(t_chunk);
					c->is_free = TRUE;
					return (b);
				}
				c = c->next;
			}
			b = b->next;
		}
	}
	return (NULL);
}

int			is_bucket_to_free(t_bucket *b)
{
	t_chunk	*tmp;
	
	if (b == g_saved_data.tiny || b == g_saved_data.small || b == g_saved_data.large)
		return (FALSE);
	tmp = b->chunks;
	while (tmp)
	{
		if (!tmp->is_free)
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

void		ft_free(void *ptr)
{
	t_bucket *b;

	if (!ptr)
		return ;
	if (!(b = get_bucket(ptr)))
	{
		printf("WTF\n");
		return ;
	}
	if (is_bucket_to_free(b))
	{
		free_bucket(b);
	}
}
