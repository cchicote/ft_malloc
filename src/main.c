/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:14:51 by cchicote          #+#    #+#             */
/*   Updated: 2018/11/07 16:14:56 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	print_chunks(t_bucket *b)
{
	t_chunk *tmp;

	tmp = b->chunks;
	while (tmp)
	{
		printf("Address: %p\n", tmp->mem);
		tmp = tmp->next;
	}
}

int		main()
{
	char		*str;
	t_bucket	*tmp;

	/*int i = 0;
	while (i < 10)
	{
		str = (char*)ft_malloc(100 * i);
		i += 10;
	}*/

	str = (char*)ft_malloc(1); 
	str = (char*)ft_malloc(1); 
	str = (char*)ft_malloc(1);
	tmp = g_saved_data.tiny;
	while (tmp)
	{
		printf("TINY: %zu/%zu\n", tmp->allocated, tmp->total_size);
		print_chunks(tmp);
		tmp = tmp->next;
	}
	tmp = g_saved_data.small;
	while (tmp)
	{
		printf("SMALL: %zu/%zu\n", tmp->allocated, tmp->total_size);
		tmp = tmp->next;
	}
	tmp = g_saved_data.large;
	while (tmp)
	{
		printf("LARGE: %zu/%zu\n", tmp->allocated, tmp->total_size);
		tmp = tmp->next;
	}

	return (0);
}
