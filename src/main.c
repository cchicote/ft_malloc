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
#define M 1024 * 1024

/*void	print_all_data(void)
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
}*/

void	test_1(void)
{
	int i;

	i = 0; 
	while (i < 1024) 
	{
		i++;
	}
}

void	test_2(void)
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
}

void	test_3(void)
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
}

void	test_4(void)
{
	char *addr1; 
	char *addr3; 

	addr1 = (char*)ft_malloc(16*M); 
	ft_strcpy(addr1, "Bonjours\n"); 
	printf("%s", addr1);
	addr3 = (char*)ft_realloc(addr1, 128*M);
	addr3[127*M] = 42;
	printf("%s", addr3);
}

void	test_5(void)
{
	char *addr1; 
	char *addr2; 
	char *addr3; 

	addr1 = (char*)ft_malloc(16*M); 
	ft_strcpy(addr1, "Bonjours\n"); 
	printf("%s", addr1); 
	addr2 = (char*)ft_malloc(16*M); 
	addr3 = (char*)ft_realloc(addr1, 128*M); 
	addr3[127*M] = 42; 
	printf("%s", addr3); 
}

void	test_6(void)
{
	char *addr; 

	addr = ft_malloc(16); 
	ft_free(NULL); 
	ft_free((void *)addr + 5); 
	if (ft_realloc((void *)addr + 5, 10) == NULL) 
		printf("%s", "Bonjours\n"); 
}

void	test_7(void)
{
	void *mem;
	
	mem = ft_malloc(1024);
	mem = ft_malloc(1024 * 32); 
	mem = ft_malloc(1024 * 1024); 
	mem = ft_malloc(1024 * 1024 * 16); 
	mem = ft_malloc(1024 * 1024 * 128);
	show_alloc_mem();
}

void	test_refragment()
{
	void *z1;
	void *z2;
	void *z3;
	void *z4;

	z1 = ft_malloc(1024);
	z2 = ft_malloc(1024);
	z3 = ft_malloc(1024);
	ft_free(z1);
	ft_free(z2);
	z4 = ft_malloc(2048 + sizeof(t_chunk));
	show_alloc_mem();
}

int main() 
{ 
	//test_1();
	//test_2();
	//test_3();
	//test_4();
	//test_5();
	//test_6();
	//test_7();
	//test_refragment();
	return (0); 
} 
