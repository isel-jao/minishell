/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 01:12:52 by isel-jao          #+#    #+#             */
/*   Updated: 2021/02/19 22:08:13 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void reset_std(t_ms *ms)
{
	dup2(ms->in, STDIN);
	dup2(ms->out, STDOUT);
}

void close_fds(t_ms *ms)
{
	ft_close(ms->fdin);
	ft_close(ms->fdout);
	ft_close(ms->pipin);
	ft_close(ms->pipout);
}

void reset_fds(t_ms *ms)
{
	ms->fdin = -1;
	ms->fdout = -1;
	ms->pipin = -1;
	ms->pipout = -1;
	ms->pid = -1;
}
