/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:26:40 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/02 19:01:48 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quotes(char *line, int index)
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

int	quote_check(t_ms *ms, char *line)
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
