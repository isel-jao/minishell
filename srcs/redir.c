/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 01:22:11 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/02 19:03:20 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir(t_ms *ms, t_token *token, int type)
{
	ft_close(ms->fdout);
	if (type == TRUNC)
		ms->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		ms->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (ms->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": Permission denied", STDERR);
		ms->ret = 1;
		ms->no_exec = 1;
		return ;
	}
	dup2(ms->fdout, STDOUT);
}

void	input(t_ms *ms, t_token *token)
{
	int				exist;
	struct stat		buffer;

	exist = stat(token->str, &buffer);
	if (exist)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		ms->ret = 1;
		ms->no_exec = 1;
		return ;
	}
	ft_close(ms->fdin);
	ms->fdin = open(token->str, O_RDONLY, S_IRWXU);
	if (ms->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": Permission denied", STDERR);
		ms->ret = 1;
		ms->no_exec = 1;
		return ;
	}
	dup2(ms->fdin, STDIN);
}

int		ft_pipe(t_ms *ms)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		ms->pipin = pipefd[0];
		ms->pid = -1;
		ms->parent = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		ms->pipout = pipefd[1];
		ms->pid = pid;
		return (1);
	}
}
