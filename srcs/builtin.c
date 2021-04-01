/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 09:16:07 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/16 16:57:39 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}




int exec_builtin(t_ms *ms, char **args)
{
	int result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(ms, args);
	if (ft_strcmp(args[0], "cd") == 0)
		result = ft_cd(ms->env, args);
	if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(ms, args);
	if (ft_strcmp(args[0], "env") == 0)
		ft_env(ms->env);
	if (ft_strcmp(args[0], "export") == 0)
		result = ft_export(ms->env, args);
	if (ft_strcmp(args[0], "unset") == 0)
		result = ft_unset(ms, args);
	return (result);
}