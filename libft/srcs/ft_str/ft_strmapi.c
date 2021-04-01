/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 21:42:35 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 15:09:02 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	if (!s || !(result = malloc((ft_strlen((char *)s) + 1))))
		return (NULL);
	ft_bzero(result, ft_strlen((char *)s) + 1);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		++i;
	}
	result[i] = '\0';
	return (result);
}
