/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 22:29:45 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 17:23:34 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void ft_prompt(int ret)
{
	int i;
	ft_putnbr_fd(ret, STDERR);
	ft_putstr_fd(" minshell> ", STDERR);
}

void redir_and_exec(t_ms *ms, t_token *token)
{
	t_token *prev;
	t_token *next;
	int pipe;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	if (is_type(prev, TRUNC))
		redir(ms, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(ms, token, APPEND);
	else if (is_type(prev, INPUT))
		input(ms, token);
	else if (is_type(prev, PIPE))
		pipe = ft_pipe(ms);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_and_exec(ms, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev) && pipe != 1 && !ms->no_exec)
		exec_cmd(ms, token);
}

void minishell(t_ms *ms)
{
	t_token *token;
	int buf;

	token = next_run(ms->token, NOSKIP);
	token = (is_types(ms->token, "TAI")) ? ms->token->next : token;
	while (ms->exit == 0 && token)
	{
		ms->charge = 1;
		ms->parent = 1;
		redir_and_exec(ms, token);
		reset_std(ms);
		close_fds(ms);
		reset_fds(ms);
		waitpid(-1, &buf, 0);
		if (ms->parent == 0)
		{
			free_token(ms);
			exit(ms->ret);
		}
		ms->no_exec = 0;
		token = next_run(token, SKIP);
	}
}
int check(t_ms *ms, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI") && (!token->next || is_types(token->next, "TAIPE")))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR);
			token->next ? ft_putstr_fd(token->next->str, STDERR) : ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			ms->ret = 2;
			return (0);
		}
		if (is_types(token, "PE") && (!token->prev || !token->next || is_types(token->prev, "TAIPE")))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR);
			ft_putstr_fd(token->str, STDERR);
			ft_putendl_fd("'", STDERR);
			ms->ret = 2;
			return (0);
		}
		if (is_types(token, "PE") && (!token->prev || is_types(token->prev, "TAIPE")))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR);
			ft_putstr_fd(token->str, STDERR);
			ft_putendl_fd("'", STDERR);
			ms->ret = 2;
			return (0);
		}
		token = token->next;
	}
	return (1);
}

void free_env(t_env *env)
{
	t_env *buf;

	while (env)
	{
		buf = env;
		ft_free(env->value);
		env = env->next;
		ft_free(buf);
	}
}

int main(int ac, char **av, char **env)
{
	t_ms ms;

	(void)ac;
	(void)av;
	ft_bzero(&ms, sizeof(t_ms));
	ms.in = dup(STDIN);
	ms.out = dup(STDOUT);
	init_env(&ms, env);
	sig_init();
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	ms.hist = retrieve_history(&ms.h_fd);
	while (ms.exit == FALSE)
	{
		sig_init();
		parse(&ms);
		if (ms.token && check(&ms, ms.token) == TRUE)
			minishell(&ms);
		free_token(&ms);
	}
	free_env(ms.env);
	return (ms.ret);
}
