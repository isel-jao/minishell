/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao  <isel-jao@student.42.f>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:11:50 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/15 19:41:44 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void appand_history(char *line, int h_fd)
{
	// int *h_fd;
	// if (h_fd)
	h_fd = open(HISTORY_PATH, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (h_fd > 0 && line && line[0])
		ft_putendl_fd(line, h_fd);
	// if (h_fd > 0)
	// close(h_fd);
}

t_list *retrieve_history(int *h_fd)
{
	// int h_fd;
	t_list *hist;
	char *line;
	size_t len;

	hist = NULL;
	*h_fd = open(HISTORY_PATH, O_CREAT | O_RDWR, 0666);
	if (*h_fd == -1)
		return (NULL);
	while (get_next_line(*h_fd, &line) > 0)
	{
		ft_lstadd_back(&hist, ft_lstnew(line));
	}
	return (hist);
}