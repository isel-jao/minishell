/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 22:29:45 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/02 18:57:38 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_prompt(int ret)
{
	ft_putnbr_fd(ret, STDERR);
	ft_putstr_fd(" minshell> ", STDERR);
}

void	redir_and_exec(t_ms *ms, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

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
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev) &&\
		pipe != 1 && !ms->no_exec)
		exec_cmd(ms, token);
}

void	minishell(t_ms *ms)
{
	t_token	*token;
	int		buf;

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

void	free_env(t_env *env)
{
	t_env	*buf;

	while (env)
	{
		buf = env;
		ft_free(env->value);
		env = env->next;
		ft_free(buf);
	}
}

int		main(int ac, char **av, char **env)
{
	t_ms	ms;

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
