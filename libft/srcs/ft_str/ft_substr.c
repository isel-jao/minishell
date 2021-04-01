/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:01:08 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 15:09:21 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	int		x;

	if (!s || !(ret = malloc(len + 1)))
		return (0);
	x = len;
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	while (start-- > 0)
		s++;
	while (len-- > 0)
		*ret++ = *s++;
	*ret = '\0';
	return (ret - x);
}
