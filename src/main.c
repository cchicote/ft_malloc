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
	char	*str;
	t_zone	*tmp;

	str = (char*)ft_malloc(sizeof(char) * 100);
	str = ft_strcpy(str, ft_strdup("HAHAHAHA"));
	printf("%s\n", str);
	munmap(str, sizeof(char) * 100);
	str = (char*)ft_malloc(sizeof(char) * 321);
	str = ft_strcpy(str, ft_strdup("HAHAHAHA"));
	printf("%s\n", str);
	munmap(str, sizeof(char) * 321);
	str = (char*)ft_malloc(sizeof(char) * 12);
	str = ft_strcpy(str, ft_strdup("HAHAHAHA"));
	printf("%s\n", str);
	munmap(str, sizeof(char) * 12);

	str = (char*)ft_malloc(TINY_MAX + 1);
	str = ft_strcpy(str, ft_strdup("HAHAHAHA"));
	printf("%s\n", str);
	munmap(str, TINY_MAX + 1);

	str = (char*)ft_malloc(SMALL_MAX + 1);
	str = ft_strcpy(str, ft_strdup("HAHAHAHA"));
	printf("%s\n", str);
	munmap(str, SMALL_MAX + 1);

	tmp = g_saved_data.tiny_head;
	while (tmp)
	{
		printf("TINY: %zu\n", tmp->size);
		tmp = tmp->next;
	}

	return (0);
}
