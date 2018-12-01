/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:02:42 by cchicote          #+#    #+#             */
/*   Updated: 2018/11/28 13:02:48 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdint.h>

static void	print_address_hex(long num, int depth)
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

void		print_bucket_start(t_bucket *bucket, char *dim)
{
	ft_putstr(dim);
	ft_putstr(": ");
	print_address_hex((long)bucket, 9);
	ft_putchar('\n');
}

void		print_chunk_data(t_chunk *c)
{
	print_address_hex((long)c + 1, 9);
	ft_putstr(" - ");
	print_address_hex((long)c + c->size, 9);
	ft_putstr(" : ");
	ft_putnbr(c->size);
	ft_putendl(" octets");
}

size_t		print_bucket(t_bucket *bucket, char *dim)
{
	t_bucket *b;
	t_chunk	*c;
	size_t total;

	b = bucket;
	if (bucket->is_free)
		return (0);
	total = 0;
	print_bucket_start(bucket, dim);
	while (b)
	{
		c = b->chunks;
		while (c)
		{
			if (!c->is_free || c->is_free)
				print_chunk_data(c);
			total += !c->is_free ? sizeof(t_chunk) + c->size : 0;
			c = c->next;
		}
		b = b->next;
	}
	return (total);
}

void		print_total(size_t total)
{
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" octets");
}

void		show_alloc_mem(void)
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
		print_total(total);
}