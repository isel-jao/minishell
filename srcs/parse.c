/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 10:11:25 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 17:29:20 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



/*
** allocat mem for the added space new line
*/

char *space_alloc(char *line)
{
	char *new;
	int count;
	int i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(line, i))
			count++;
		i++;
	}
	if (!(new = malloc(sizeof(char) * (i + 2 * count + 1))))
		return (NULL);
	return (new);
}

/*
** add spaces arround separators and mark expantions positions
*/

char *sep_space(char *line)
{
	char *new;
	int i;
	int j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new &&line[i])
	{
		if (quotes(line, i) != QOUTE && line[i] == '$' && i && line[i - 1] != '\\')
		{
			new[j++] = EXPANSION;
			i++;
		}
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i - 1] == '>' && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	return (new);
}


void prompt(t_ms *ms)
{
	int ret = ms->ret;
	int i = 0;
	int a = 100;
	while (a)
	{
		ms->prompt[i++] = ret / a + 48;
		ret %= a;
		a /= 10;
	}
	ft_memcpy(&ms->prompt[i], " minishell > ", 14);
}

void parse(t_ms *ms)
{
	char *line;

	line = NULL;
	prompt(ms);
	if (!(ms->line = ft_readline(ms->prompt, ms->hist, &ms->exit, &ms->ret)) )
		return;
	ft_putchar('\n');
	appand_history(ms->line, ms->h_fd);
	if (!ft_strcmp(ms->line, "history"))
	{
		print_history(ms->hist);
		return;
	}
	if (ms->line && ms->line[0])
			ft_lstadd_back(&ms->hist, ft_lstnew(ms->line));
	if (quote_check(ms, ms->line))
		return;
	ms->line = sep_space(ms->line);
	if (ms->line && ms->line[0] == '$')
		ms->line[0] = EXPANSION;
	ms->token = get_tokens(ms->line);
	sort_args(ms);
	ft_free(ms->line);
}