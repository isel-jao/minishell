/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:27:53 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/03 10:52:58 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			ft_skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t') || (str[*i] == '\r' || \
	str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

static void		sub_next_token(t_token *token, char *line, int *i, char c)
{
	int		j;

	j = 0;
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && line[*i] == '\"' && (c = line[*i]))
			token->str[j++] = line[(*i)++];
		else if (c == ' ' && line[*i] == '\'')
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			if (c == '\"')
				token->str[j++] = c;
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && !quotes(line, *i) && (*i)++)
			token->str[j++] = line[(*i)++];
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
}

t_token			*next_token(char *line, int *i)
{
	int		j;
	t_token	*token;
	char	c;

	j = 0;
	c = ' ';
	if (!(token = malloc(sizeof(t_token))) || \
	!(token->str = malloc(sizeof(char) * token_len(line, i))))
		return (NULL);
	sub_next_token(token, line, i, c);
	return (token);
}

void			type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

t_token			*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
