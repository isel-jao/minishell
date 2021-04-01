/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:04:43 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/01 15:59:52 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int update_oldpwd(t_env *env)
{
	char *cwd;
	char *oldpwd;

	oldpwd = NULL;
	cwd = env_value(env, "PWD");
	if (cwd)
	{
		if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
			return (ERROR);
		export_env(env, oldpwd, 6);
		ft_free(oldpwd);
	}
	return (SUCCESS);
}
int update_pwd(t_env *env)
{
	char cwd[PATH_MAX];
	char *newpwd;

	newpwd = NULL;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	if (!(newpwd = ft_strjoin("PWD=", cwd)))
		return (ERROR);
	export_env(env, newpwd, 3);
	ft_free(newpwd);
	return (SUCCESS);
}

int go_to_path(int option, t_env *env)
{
	int ret;
	char *env_path;

	env_path = NULL;
	if (option == 0)
	{
		env_path = env_value(env, "HOME");
		if (!env_path)
		{
			ft_putendl_fd("minishell : cd: HOME not set", STDERR);
			return (ERROR);
		}
	}
	else if (option == 1)
	{
		env_path = env_value(env, "OLDPWD");
		if (!env_path)
		{
			ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR);
			return (ERROR);
		}
		ft_putendl(env_path);
	}
	ret = chdir(env_path);
	update_oldpwd(env);
	update_pwd(env);
	return (ret);
}