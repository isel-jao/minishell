/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:18:00 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 15:20:08 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**new_tab(size_t size)
{
	void	**tab;
	int		mem_size;

	mem_size = size * __SIZEOF_POINTER__;
	if ((tab = malloc(mem_size)))
		ft_bzero(tab, mem_size);
	return (tab);
}
