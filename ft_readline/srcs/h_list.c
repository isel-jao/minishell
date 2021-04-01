/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao  <isel-jao@student.42.f>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:09:52 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/15 19:41:44 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int ft_lstsize(t_list *tail)
{
	int i;

	i = 0;
	if (!tail)
		return (0);
	while (tail->prev && ++i)
		tail = tail->prev;
	return (i);
}

t_list *ft_lstnew(void *content)
{
	t_list *new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	ft_bzero(new, sizeof(t_list));
	new->content = content;
	return (new);
}
t_list *ft_lstadd_back(t_list **list, t_list *new)
{
	if (!new)
		return (NULL);
	if (!(*list))
	{
		*list = new;
		return (*list);
	}
	while ((*list)->next)
		*list = (*list)->next;
	(*list)->next = new;
	new->prev = *list;
	*list = new;
	return (*list);
}

void ft_lstremovenode(t_list **hist)
{
	t_list *tmp;
	if (!hist)
		return;
	ft_free((*hist)->content);
	tmp = *hist;
	*hist = (*hist)->prev;
	if (*hist)
		(*hist)->next = NULL;
	free(tmp);
}