/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:04:43 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/05 10:45:33 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			update_oldpwd(t_env *env)
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

int			update_pwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*newpwd;

	newpwd = NULL;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	if (!(newpwd = ft_strjoin("PWD=", cwd)))
		return (ERROR);
	export_env(env, newpwd, 3);
	ft_free(newpwd);
	return (SUCCESS);
}

static int	ft_error(int option)
{
	if (option == 0)
		ft_putendl_fd("minishell : cd: HOME not set", STDERR);
	else if (option == 1)
		ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR);
	return (ERROR);
}

static	int	ft_chdir(char *env_path, t_env *env)
{
	int		ret;

	ret = chdir(env_path);
	if (ret != 0)
		print_cd_error(&env_path);
	else
	{
		update_oldpwd(env);
		update_pwd(env);
	}
	return (ret);
}

int			go_to_path(int option, t_env *env)
{
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		env_path = env_value(env, "HOME");
		if (!env_path)
			return (ft_error(option));
	}
	else if (option == 1)
	{
		env_path = env_value(env, "OLDPWD");
		if (!env_path)
			return (ft_error(option));
		ft_putendl(env_path);
	}
	return (ft_chdir(env_path, env));
}
