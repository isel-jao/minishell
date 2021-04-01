/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 09:20:08 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/01 16:14:28 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void ft_env_secret(t_env *env);


void export_env(t_env *env, char *key, int len)
{
	t_env *tmp;
	
	tmp = env;
	while (tmp && ft_strncmp(tmp->value, key, len))
		tmp = tmp->next;
	if (tmp)
	{
		ft_free(tmp->value);
		tmp->value = ft_strdup(key);
	}
	else
		add_env(env, key);
}

static int print_error(char *s)
{
	ft_putstr_fd("bash: export: `", STDERR);
	ft_putstr_fd(s, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
	return (1);
}

static int is_valid(const char *s)
{
	int i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (-1);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (-1);
		i++;
	}
	if (s[i] != '=')
		return (1);
	return (0);
}

int ft_export(t_env *env, char **args)
{
	int i;
	int k;
	int ret;
	ret = 0;
	i = 1;
	while (args[i])
	{
		k = is_valid(args[i]);
		if (k == -1)
			ret = print_error(args[i]);
		else
			export_env(env, args[i], env_len(args[i]));
		i++;
	}
	if (i == 1)
		ft_env_secret(env);
	char *tmp;
	tmp = ft_strjoin("_=", args[tab_len((void **)args)  - 1]);
	export_env(env, tmp, 1);
	ft_free(tmp);
	return (ret);
}