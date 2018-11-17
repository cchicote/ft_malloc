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

int		main(void)
{
	char *str;

	str = (char*)ft_malloc(sizeof(char) * 100);
	if (!str)
		printf("ERROR\n");
	munmap(str, sizeof(str));
	return (0);
}