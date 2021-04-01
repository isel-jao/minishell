/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 22:30:17 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 15:09:14 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *last;

	last = (0);
	while (*s)
	{
		if (*s == (char)c)
			last = (char *)s;
		++s;
	}
	if (last)
		return (last);
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}
