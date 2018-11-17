/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:12:24 by cchicote          #+#    #+#             */
/*   Updated: 2018/11/07 16:12:26 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*ft_malloc(size_t size)
{
	void	*ptr;
	t_zone	*zone;

	ptr = NULL;
	zone = NULL;
	if (!size)
		return (ptr);
	if (size <= (size_t)TINY_MAX)
	{
		printf("TINY %zu\n", new_zone(size, TINY)->size);
	}
	else if (size <= (size_t)SMALL_MAX)
	{
		printf("SMALL %zu\n", new_zone(size, SMALL)->size);
	}
	else if (size > (size_t)SMALL_MAX)
	{
		printf("LARGE %zu\n", new_zone(size, LARGE)->size);
	}
	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
	return (ptr);
}
