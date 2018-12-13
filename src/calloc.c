/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 22:13:52 by cchicote          #+#    #+#             */
/*   Updated: 2018/12/13 22:13:58 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	align(size_t size, size_t align)
{
	size_t	shift;
	size_t	temp;

	if (size <= align)
		return (align);
	temp = align;
	shift = 0;
	while (temp >= 2)
	{
		shift++;
		temp >>= 1;
	}
	return ((((size - 1) >> shift) << shift) + align);
}

void				*calloc(size_t count, size_t size)
{
    void            *ret;

    if (!count || !size)
        return (NULL);
    ret = malloc(count * size);
    if (ret)
        ft_bzero(ret, align(count * size, 16));
    return (ret);
}