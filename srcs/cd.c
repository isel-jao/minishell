/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 09:19:08 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/01 15:51:28 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

int ft_sub_cd(t_env *env, char **args)
{
	int ret;
	
	if (!args[1])
		return (go_to_path(0, env));
	else if (ft_strcmp(args[1], "-") == 0)
		return (go_to_path(1, env));
	else
	{
		ret = chdir(args[1]);
		if (ret != 0)
			print_error(args);
		else
		{
			update_oldpwd(env);
			update_pwd(env);
		}
	}
	return (ret != 0);
}
int ft_cd(t_env *env, char **args)
{
	char *tmp;
	char buf[PATH_MAX];
	char *cwd;

	if (tab_len((void **)args) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR);
		return (1);
	}
	cwd = getcwd(buf, PATH_MAX);
	if (!cwd && (!ft_strcmp(args[1], ".") ))
		ft_putendl_fd("cd: error retrieving current directory:\
getcwd: cannot access parent directories: No such file or directory", 2);
	return(ft_sub_cd(env, args));
}