/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:07:06 by yqodsi            #+#    #+#             */
/*   Updated: 2021/04/02 18:28:53 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_exit(t_ms *ms, char **cmd)
{
	ms->exit = 1;
	ft_putstr_fd("exit\n", STDERR);
	if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		ms->exit = 0;
		ms->ret = 2;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (cmd[1] && cmd[2])
	{
		ms->exit = 0;
		ms->ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	}
	else if (cmd[1])
		ms->ret = ft_atoi(cmd[1]);
	else
		ms->ret = 0;
}
