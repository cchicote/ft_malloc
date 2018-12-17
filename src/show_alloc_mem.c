/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:26:32 by cchicote          #+#    #+#             */
/*   Updated: 2018/12/13 16:26:38 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			print_address_hex(long num, int depth)
{
	if (depth == 0)
	{
		write(1, "0x", 2);
		return ;
	}
	print_address_hex(num >> 4, depth - 1);
	num -= (num >> 4) << 4;
	if (num < 10)
		num += '0';
	else
		num += 55;
	write(1, &num, 1);
}

void			print_bucket_start(t_bucket *bucket, char *dim)
{
	ft_putstr(dim);
	ft_putstr(": ");
	print_address_hex((long)bucket, 9);
	ft_putchar('\n');
}

size_t			print_chunk_data(t_chunk c)
{
	print_address_hex((long)c.mem, 9);
	ft_putstr(" - ");
	print_address_hex((long)c.mem + c.size - sizeof(t_chunk), 9);
	ft_putstr(" : ");
	ft_putnbr(c.size);
	ft_putendl(" octets");
	return (c.size);
}

size_t			print_bucket(t_bucket *bucket, char *dim)
{
	t_bucket	*b;
	size_t		i;
	size_t		total;

	b = bucket;
	total = 0;
	if (is_bucket_free(bucket))
		return (0);
	print_bucket_start(bucket, dim);
	while (b)
	{
		i = 0;
		while (i < b->chunks)
		{
			if (b->chunks_tab[i].size)
				total += print_chunk_data(b->chunks_tab[i]);
			i++;
		}
		b = b->next;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	size_t total;

	total = 0;
	if (g_saved_data.tiny)
		total += print_bucket(g_saved_data.tiny, "TINY");
	if (g_saved_data.small)
		total += print_bucket(g_saved_data.small, "SMALL");
	if (g_saved_data.large)
		total += print_bucket(g_saved_data.large, "LARGE");
	if (total > 0)
	{
		ft_putstr("Total : ");
		ft_putnbr(total);
		ft_putendl(" octets");
	}
}
