/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:53:07 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/02 12:17:19 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_closedir(DIR *folder)
{
	if (folder)
		closedir(folder);
}

int error_message(char *path)
{
	DIR *folder;
	int fd;
	int ret;

	ret = SUCCESS;
	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	ft_closedir(folder);
	ft_close(fd);
	return (ret);
}

char *path_join(const char *s1, const char *s2)
{
	char *tmp;
	char *path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_free(tmp);
	return (path);
}

char *check_dir(char *bin, char *command)
{
	DIR *folder;
	struct dirent *item;
	char *path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, command) == 0)
			path = path_join(bin, item->d_name);
	}
	closedir(folder);
	return (path);
}

int ft_execve(char *path, char **args,  t_ms *ms)
{
	char **env_array;
	int ret;

	ret = SUCCESS;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		
		env_array = lst_to_tab(ms->env);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = error_message(path);
		free_tab((void **)env_array);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.exit_status)
		return	(g_sig.exit_status);
	ret = WEXITSTATUS(ret);
	return (ret);
}

int exec_bin(char **args, t_env *env, t_ms *ms)
{
	int i;
	char **bin;
	char *path;
	int ret;

	i = 0;
	ret = UNKNOWN_COMMAND;
	while (env && ft_strncmp(env->value, "PATH=", 5))
		env = env->next;
	if (env == NULL)
		return (ft_execve(args[0], args,  ms));
	bin = ft_split(env->value, ':');
	if (!args[0] && !bin[0])
		return (ERROR);
	path = check_dir(&bin[0][5], args[0]);
	i = 1;
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	if (path != NULL)
		ret = ft_execve(path, args,  ms);
	else
		ret = ft_execve(args[0], args,  ms);
	free_tab((void **)bin);
	ft_free(path);
	return (ret);
}
