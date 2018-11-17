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

	ptr = NULL;
	if (!size)
		return (ptr);
	if (size <= N)
	{
		// TINY ZONE
	}
	else if (size <= M)
	{
		// SMALL ZONE
	}
	else if (size > M)
	{
		// LARGE ZONE
	}

	return (ptr);
}

