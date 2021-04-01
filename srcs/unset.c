/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 09:19:56 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 14:48:59 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int print_error(char *s)
{
	ft_putstr_fd("minshell: unset: `", STDERR);
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
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}
void unset_env(t_ms *ms, char *key)
{
	t_env *node;
	int len;
	int key_len;

	len = ft_strlen(key);
	node = ms->env;
	while (node)
	{
		key_len = env_len(node->value);
		if (len == key_len && !ft_strncmp(node->value, key, len))
		{
			del_node(&ms->env, node);
			return;
		}
		node = node->next;
	}
}

int ft_unset(t_ms *ms, char **args)
{
	int i;
	int k;
	int ret;
	char *tmp;
	ret = 0;
	i = 1;
	while (args[i])
	{
		k = is_valid(args[i]);
		if (k == -1)
			ret = print_error(args[i]);
		else if (k == 0)
			unset_env(ms, args[i]);
		i++;
	}
	tmp = ft_strjoin("_=", args[tab_len((void **)args)  - 1]);
	export_env(ms->env, tmp, 1);
	ft_free(tmp);
	return (ret);

}