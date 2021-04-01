/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 13:03:06 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 15:15:37 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lst_add_back(t_lst **lst, t_lst *new)
{
	if (!new)
		return (NULL);
	if (!(*lst))
	{
		*lst = new;
		return (*lst);
	}
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new;
	new->prev = *lst;
	*lst = new;
	return (*lst);
}
