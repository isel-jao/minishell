/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao  <isel-jao@student.42.f>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 19:35:56 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 02:46:20 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int main(int argc, char const *argv[])
{
	int ms_exit = 0;
	int ms_ret = 0;
	char *line;
	t_list *hist;
	hist = NULL;
	int h_fd;
	hist = retrieve_history(&h_fd);
	while (1)
	{
		line = ft_readline("minishell > ", hist, &ms_exit, &ms_ret);
		if (line && line[0])
			ft_lstadd_back(&hist, ft_lstnew(line));
		ft_putstr("\n");
		appand_history(line, h_fd);
		if (!ft_strcmp(line, "exit"))
			exit(0);
		else if (!ft_strcmp(line, "hist"))
			print_history(hist);
		else if (line)
			printf("%s\n", line);
		if (ms_exit)
		{
			ft_putstr_fd("exit by \"CTRL_D\"\n", 1);
			exit(0);
		}
	}
	return 0;
}