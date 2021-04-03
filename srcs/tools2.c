/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 10:19:21 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/03 10:24:32 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	las_cmd(t_ms *ms, char **args)
{
	char *tmp;

	tmp = ft_strjoin("_=", args[tab_len((void **)args) - 1]);
	export_env(ms->env, tmp, 1);
	ft_free(tmp);
}

char	**lst_to_tab(t_env *lst)
{
	size_t	len;
	char	**table;
	int		i;

	if (!lst)
		return (NULL);
	len = size_env(lst);
	table = malloc(sizeof(char **) * (len + 1));
	i = 0;
	while (lst)
	{
		table[i++] = lst->value;
		lst = lst->next;
	}
	table[i] = NULL;
	return (table);
}

size_t	size_env(t_env *lst)
{
	size_t lst_len;

	lst_len = 0;
	while (lst)
	{
		lst_len++;
		lst = lst->next;
	}
	return (lst_len);
}

int		env_len(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

char	*env_value(t_env *env, char *key)
{
	t_env	*tmp;
	char	*s;
	int		len;
	int		key_len;

	len = ft_strlen(key);
	tmp = env;
	while (tmp)
	{
		s = tmp->value;
		key_len = env_len(s);
		if (len == key_len && !ft_strncmp(s, key, len))
			return (&s[len + 1]);
		tmp = tmp->next;
	}
	return (NULL);
}
