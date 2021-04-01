/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:26:40 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 17:27:04 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** check if there is an open quote before the givin index 
*/

int quotes(char *line, int index)
{
	int i;
	int open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (open == 0 && i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\"')
			open = DQOUTE;
		else if (open == 0 && line[i] == '\'')
			open = QOUTE;
		else if (open == DQOUTE && line[i] == '\"')
			open = 0;
		else if (open == QOUTE && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

/*
** check open quotes error
*/
int quote_check(t_ms *ms, char *line)
{
	if (quotes(line, 2147483647))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		ms->ret = 2;
		ms->token = NULL;
		return (1);
	}
	return (0);
}