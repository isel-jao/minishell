/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_remove_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 13:04:50 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 15:19:54 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_remove_node(t_lst **lst)
{
	t_lst *tmp;

	if (!lst)
		return ;
	ft_free((*lst)->content);
	tmp = *lst;
	if (!(*lst)->prev)
	{
		*lst = (*lst)->next;
		(*lst)->prev = tmp->prev;
		free(tmp);
		return ;
	}
	*lst = (*lst)->prev;
	(*lst)->next = tmp->next;
	free(tmp);
}
