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
	int			total_buckets;
	int			total_chunks;
	int			i;

	i = 0;
	total_buckets = 0;
	total_chunks = 0;
	while (i < 3)
	{
		b = tab[i];
		while (b)
		{
			total_buckets++;
			print_bucket_specs(b, STANDARD);
			c = b->chunks;
			while (c)
			{
				total_chunks++;
				//print_chunk_specs(c);
				c = c->next;
			}
			b = b->next;
		}
		i++;
	}
	printf("Buckets: [%d]\nChunks: [%d]\n", total_buckets, total_chunks);
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
		ft_free(addr);
		i++;
	}
	print_all_data();
	return (0); 
} 
