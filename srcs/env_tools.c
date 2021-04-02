/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 18:48:50 by yqodsi            #+#    #+#             */
/*   Updated: 2021/04/02 18:49:01 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (TRUE);
	return (FALSE);
}
