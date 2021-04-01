/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:32:03 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 15:08:47 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		i;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	i = (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!(ret = ft_memalloc(i)))
		return (NULL);
	while (*s1)
	{
		*ret = *s1;
		ret++;
		s1++;
	}
	while (*s2)
	{
		*ret = *s2;
		ret++;
		s2++;
	}
	*ret = '\0';
	return (ret - i + 1);
}
