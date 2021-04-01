/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao  <isel-jao@student.42.f>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 01:30:55 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/01 18:11:17 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ret_size(int ret)
{
	char *tmp;
	int ret_len;

	tmp = ft_itoa(ret);
	ret_len = ft_strlen(tmp);
	ft_free(tmp);
	return (ret_len);
}

int get_var_len(const char *arg, int pos, t_env *env, int ret)
{
	char var_name[BUFF_SIZE];
	char *var_value;
	int i;

	i = 0;
	if (arg[pos] == '?')
		return (ret_size(ret));
	if (ft_isdigit(arg[pos]))
		return (0);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	i = ft_strlen(var_value);
	ft_free(var_value);
	return (i);
}

int arg_alloc_len(const char *arg, t_env *env, int ret)
{
	int i;
	int size;

	i = -1;
	size = 0;
	while (arg[++i])
	{
		if (arg[i] == EXPANSION)
		{
			i++;
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
				size++;
			else
				size += get_var_len(arg, i, env, ret);
			if (ft_isdigit(arg[i]) == 0)
			{
				while (arg[i + 1] && is_env_char(arg[i]))
					i++;
			}
			else
				size--;
		}
		size++;
	}
	return (size);
}

char *get_var_value(const char *arg, int pos, t_env *env, int ret)
{
	char var_name[BUFF_SIZE];
	char *var_value;
	int i;

	i = 0;
	if (arg[pos] == '?')
	{
		var_value = ft_itoa(ret);
		return (var_value);
	}
	if (ft_isdigit(arg[pos]))
		return (NULL);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	return (var_value);
}

static int varlcpy(char *new_arg, const char *env_value, int pos)
{
	int i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

static void insert_var(t_expansions *ex, char *arg, t_env *env, int ret)
{
	char *env_value;

	env_value = get_var_value(arg, ex->j, env, ret);
	ex->i += env_value ? varlcpy(ex->new_arg, env_value, ex->i) : 0;
	ft_free(env_value);
	arg[ex->j] == '?' ? ex->j++ : 0;
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
	{
		while (is_env_char(arg[ex->j]) == 1)
			ex->j++;
	}
	else
	{
		if (arg[ex->j - 1] != '?')
			ex->j++;
	}
}

char *expansions(char *arg, t_env *env, int ret)
{
	t_expansions ex;
	int new_arg_len;

	new_arg_len = arg_alloc_len(arg, env, ret);
	if (!(ex.new_arg = malloc(sizeof(char) * new_arg_len + 1)))
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < new_arg_len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANSION)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0) && arg[ex.j] != '?' && arg[ex.j] != '_')
				ex.new_arg[ex.i++] = '$';
			else
				insert_var(&ex, arg, env, ret);
		}
		if (arg[ex.j] != '\"' && (arg[ex.j] != '\\' || arg[ex.j + 1] != '$') )
			ex.new_arg[ex.i++] = arg[ex.j];
		ex.j++;
	}
	ex.new_arg[ex.i] = '\0';
	if (ex.new_arg[0] == 0 && !ft_strchr(arg, '\"'))
	{
		ft_free(ex.new_arg);
		return NULL;
	}
	return (ex.new_arg);
}