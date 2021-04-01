/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 13:01:42 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 15:17:32 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst *new;

	if (!(new = malloc(sizeof(t_lst))))
		return (NULL);
	ft_bzero(new, sizeof(t_lst));
	new->content = content;
	return (new);
}
