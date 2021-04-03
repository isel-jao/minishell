/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 13:08:43 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/03 10:22:57 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		free_node(t_env *node)
{
	if (!node)
		return ;
	ft_free(node->value);
	free(node);
}

void		del_node(t_env **env, t_env *node)
{
	t_env *tmp;
	t_env *buf;

	tmp = *env;
	if (node == tmp)
	{
		*env = tmp->next;
		free_node(tmp);
		return ;
	}
	while (tmp && tmp->next && tmp->next != node)
		tmp = tmp->next;
	if (!tmp || !tmp->next)
		return ;
	if (tmp->next->next)
	{
		buf = tmp->next;
		tmp->next = tmp->next->next;
		free_node(buf);
		return ;
	}
	free_node(tmp->next);
	tmp->next = NULL;
}

t_env		*new_env(char *value)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void		add_env(t_env *env, char *value)
{
	t_env *new;

	new = new_env(value);
	while (env->next)
		env = env->next;
	env->next = new;
}

void		init_env(t_ms *ms, char **env)
{
	t_sl	sl;
	int		i;

	if (!env[0])
	{
		getcwd(sl.cwd, PATH_MAX);
		sl.buf = ft_strjoin("PWD=", sl.cwd);
		ms->env = new_env(sl.buf);
		add_env(ms->env, "SHLVL=1");
	}
	else
	{
		ms->env = new_env(env[0]);
		i = 1;
		while (env[i])
			add_env(ms->env, env[i++]);
		sl.shl = ft_atoi(env_value(ms->env, "SHLVL")) + 1;
		sl.buf = ft_itoa(sl.shl);
		sl.shlvl = ft_strjoin("SHLVL=", sl.buf);
		export_env(ms->env, sl.shlvl, 5);
		ft_free(sl.buf);
		ft_free(sl.shlvl);
	}
}
