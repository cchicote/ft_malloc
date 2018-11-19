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

int		main()
{
	char		*str;
	t_bucket	*tmp;

	tmp = g_saved_data.tiny;
	str = (char*)ft_malloc(1);
	str = (char*)ft_malloc(1);
	
	while (tmp)
	{
		printf("TINY: %zu\n", tmp->size);
		tmp = tmp->next;
	}

	return (0);
}
