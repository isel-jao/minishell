/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 00:55:30 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/16 14:16:28 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void print_history(t_list *hist)
{
	if (!hist)
		return;
	while (hist->prev)
	{
		hist = hist->prev;
	}
	while (hist)
	{
		ft_putendl(hist->content);
		hist = hist->next;
	}
}

static void feed_line(t_line *line, char *entry)
{
	cursor_to_home(line);
	tputs(tgetstr("cd", NULL), 0, &tc_putc);
	ft_bzero(line->cmd, MAX_CMD_LEN);
	ft_strcpy(line->cmd, entry);
	line->cursor = ft_strlen(entry);
	line->length = line->cursor;
}

void new_hist_entry(t_line *line, t_list **hist)
{
	if (!line->hist || !line->hist_depth)
	{
		return;
	}
	line->hist_depth--;
	*hist = (*hist)->next;
	feed_line(line, (*hist)->content);
	ft_putstr_fd(line->cmd, 1);
	if (!line->hist_depth)
		ft_lstremovenode(hist);
}

void old_hist_entry(t_line *line, t_list **hist)
{
	if (!line->hist || line->hist_depth > line->hist_size)
		return;
	if (!line->hist_depth)
		ft_lstadd_back(hist, ft_lstnew((void *)ft_strdup(line->cmd)));
	*hist = (*hist)->prev;
	line->hist_depth++;
	feed_line(line, (*hist)->content);
	ft_putstr_fd(line->cmd, 1);
}
