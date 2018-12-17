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

void				*calloc(size_t count, size_t size)
{
	void			*ret;

	if (!count || !size)
		return (NULL);
	ret = malloc(count * size);
	if (ret)
		ft_bzero(ret, count * size);
	return (ret);
}
