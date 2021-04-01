/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:27:53 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/01 14:50:29 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** print thokens
*/

void print_token(t_token *t)
{
	if (!t)
		return;
	while (t->prev)
		t = t->prev;
	while (t)
	{
		ft_putnbr_fd(t->type, 1);
		ft_putstr_fd("\t", 1);
		ft_putendl(t->str);
		t = t->next;
	}
}

/*
**	skip white spaces
*/

void ft_skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t') || (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

/*
** calcul length of the tokn in given index 
*/

int token_len(char *line, int *i)
{
	int count;
	int j;
	char c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

/*
** allocat and assign the next token str 
*/

t_token *next_token(char *line, int *i)
{
	t_token *token;
	int j;
	char c;

	j = 0;
	c = ' ';
	if (!(token = malloc(sizeof(t_token))) || !(token->str = malloc(sizeof(char) * token_len(line, i))))
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && line[*i] == '\"')
		{
			c = line[*i];
			token->str[j++] = line[(*i)++];
		}
		else if (c == ' ' && line[*i] == '\'' )
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			if (c == '\"')
			token->str[j++] = c;
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' &&  !quotes(line, *i) && (*i)++)
			token->str[j++] = line[(*i)++];
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
	return (token);
}

/*
** cheke if there is a separotor at the givin index
*/

int is_sep(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>|;", line[i]))
		return (0);
	else if (ft_strchr("<>|;", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
}

/*
** return lenth of the separators  
*/

int ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>' && line[i + 2] && line[i + 2] == '>')
		return (1);
	return (0);
}

/*
** set the tipe for the thoken at the given index
*/

void type_arg(t_token *token, int separator)
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

/*
** get tokens from line
*/

t_token *get_tokens(char *line)
{
	t_token *prev;
	t_token *next;
	int i;
	int sep;

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