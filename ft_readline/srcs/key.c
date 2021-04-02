/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:04:35 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/02 13:17:06 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		get_key(void)
{
	unsigned int	key_pressed;

	key_pressed = 0;
	read(0, ((void *)(&key_pressed)), MAX_KEY_LEN);
	return (key_pressed);
}

void	ctrl_l(t_line *line)
{
	tputs(tgetstr("cl", NULL), 0, &tc_putc);
	ft_putstr_fd(line->prompt, 0);
	line->start.col = ft_strlen(line->prompt) + 1;
	line->start.row = 0;
	ft_putstr_fd(line->cmd, 0);
	set_curpos(line);
}

void	ctrl_u(t_line *line)
{
	cursor_to_home(line);
	ft_bzero(line->cmd, line->length);
	tputs(tgetstr("cd", NULL), 0, &tc_putc);
}

void	match_move(int key_pressed, t_line *line)
{
	if (key_pressed == KEYCODE_R)
		cursor_to_right(line);
	else if (key_pressed == KEYCODE_L)
		cursor_to_left(line);
	else if (key_pressed == KEYCODE_HOME)
		cursor_to_home(line);
	else if (key_pressed == KEYCODE_END)
		cursor_to_end(line);
	else if (key_pressed == CTRL_L)
		ctrl_l(line);
	else if (key_pressed == CTRL_U)
		ctrl_u(line);
}

void	match_hist(int key_pressed, t_line *line)
{
	if (key_pressed == KEYCODE_U)
		old_hist_entry(line, &line->hist);
	else if (key_pressed == KEYCODE_D)
		new_hist_entry(line, &line->hist);
}
