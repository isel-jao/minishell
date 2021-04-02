/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 09:19:31 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/02 18:20:16 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	n_option;
	int	s_option;

	i = 1;
	n_option = 0;
	s_option = 0;
	if (tab_len((void **)args) > 1)
	{
		while (ft_strcmp(args[i], "-n") == 0 && (n_option = 1))
			i++;
		while (args[i])
		{
			if (s_option)
				write(1, " ", 1);
			ft_putstr_fd(args[i], 1);
			s_option = 1;
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
