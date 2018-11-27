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

void	print_all_data(void)
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
			print_bucket_specs(b, STANDARD);
			c = b->chunks;
			while (c)
			{
				print_chunk_specs(c);
				c = c->next;
			}
			b = b->next;
		}
		i++;
	}
}

int main() 
{ 
	int i; 
	char *addr; 

	i = 0; 
	while (i < 1024) 
	{ 
		addr = (char*)ft_malloc(1024); 
		addr[0] = 42; 
		i++; 
	} 
	return (0); 
} 
