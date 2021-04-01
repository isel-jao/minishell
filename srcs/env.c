/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:10:32 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/16 14:40:50 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_env(t_env *env)
{
	export_env(env, "_=env", 1);
	while (env)
	{
		if (ft_strchr(env->value, '='))
			ft_putendl(env->value);
		env = env->next;
	}
}

int lst_len(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return i;
}

char **lst_totab(t_env *env)
{
	char **table;
	int len;
	int i;

	len = lst_len(env);
	table = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		table[i] = env->value;
		env = env->next;
		i++;
	}
	table[len] = NULL;
	return (table);
}

void sort_tab(char **table)
{
	int i;
	char *tmp;
	int flag = 1;

	while (flag)
	{
		flag = 0;
		i = 0;
		while (table[i + 1])
		{
			if (ft_strcmp(table[i], table[i + 1]) > 0)
			{
				tmp = table[i + 1];
				table[i + 1] = table[i];
				table[i] = tmp;
				flag = 1;
			}
			i++;
		}
	}
}

void ft_env_secret(t_env *env)
{
	char **table;
	int i;

	i = 0;
	table = lst_totab(env);
	sort_tab(table);
	while (table[i])
	{
		if (ft_strncmp(table[i], "_=", 2))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putendl(table[i]);
		}
		i++;
	}
	ft_free(table);
}