/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 09:19:48 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/01 18:39:09 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_pwd(t_ms *ms, char **args)
{
	char cwd[PATH_MAX];
	// char *tmp;
	// tmp = ft_strjoin("_=", args[tab_len((void **)args) - 1]);
	// export_env(ms->env, tmp, 1);
	// ft_free(tmp);
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
