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

t_global 	g_saved_data;

void		push_to_end(t_zone **head, t_zone *elem)
{
	t_zone *tmp;

	tmp = *head;
	if (!tmp)
	{
		tmp = elem;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = elem;
}

t_zone		*new_zone(size_t size, int type)
{
	t_zone *new;

	if (type == TINY)
	{
		new = (t_zone*)mmap(NULL, sizeof(t_zone), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);	
		if (g_saved_data.tiny_head)
			push_to_end(&g_saved_data.tiny_head, new);
		else
			g_saved_data.tiny_head = new;
	}
	else if (type == SMALL)
	{
		new = (t_zone*)mmap(NULL, sizeof(t_zone), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
		g_saved_data.small_head = new;
	}
	else
	{
		new = (t_zone*)mmap(NULL, sizeof(t_zone), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
		g_saved_data.large_head = new;
	}
	new->size = size;
	new->type = type;
	new->next = NULL;
	return (new);
}
