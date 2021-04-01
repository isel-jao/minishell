/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:56:25 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 15:18:02 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_lst *lst)
{
	int i;

	i = 0;
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	while (lst->prev && ++i)
		lst = lst->prev;
	return (i);
}
