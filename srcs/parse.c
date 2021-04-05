/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 10:11:25 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/05 10:32:41 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check(t_ms *ms, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI") && (!token->next ||\
		is_types(token->next, "TAIPE")))
		{
			ft_putstr_fd(SYNERR, STDERR);
			token->next ? ft_putstr_fd(token->next->str, STDERR) :\
			ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			ms->ret = 258;
			return (0);
		}
		if ((is_types(token, "PE") && (!token->prev ||\
		is_types(token->prev, "TAIPE"))) || (is_types(token, "P") && \
		!token->next))
		{
			ft_putstr_fd(SYNERR, STDERR);
			ft_putstr_fd(token->str, STDERR);
			ft_putendl_fd("'", STDERR);
			ms->ret = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}

char	*space_alloc(char *line)
{
	char	*new;
	int		count;
	int		i;

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

char	*sep_space(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) != QOUTE && line[i] == '$' && \
		i && line[i - 1] != '\\' && (new[j++] = EXPANSION))
			i++;
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

void	prompt(t_ms *ms)
{
	int ret;
	int i;
	int a;

	i = 0;
	ret = ms->ret;
	a = 100;
	while (a)
	{
		ms->prompt[i++] = ret / a + 48;
		ret %= a;
		a /= 10;
	}
	ft_memcpy(&ms->prompt[i], " minishell > ", 14);
}

void	parse(t_ms *ms)
{
	char *line;

	line = NULL;
	prompt(ms);
	if (!(ms->line = ft_readline(ms->prompt, ms->hist, &ms->exit, &ms->ret)))
		return ;
	ft_putchar('\n');
	appand_history(ms->line, ms->h_fd);
	if (!ft_strcmp(ms->line, "history"))
	{
		print_history(ms->hist);
		return ;
	}
	if (ms->line && ms->line[0])
		ft_lstadd_back(&ms->hist, ft_lstnew(ms->line));
	if (quote_check(ms, ms->line))
		return ;
	ms->line = sep_space(ms->line);
	if (ms->line && ms->line[0] == '$')
		ms->line[0] = EXPANSION;
	ms->token = get_tokens(ms->line);
	sort_args(ms);
	ft_free(ms->line);
}
