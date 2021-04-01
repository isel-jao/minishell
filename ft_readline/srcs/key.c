/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:04:35 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/18 11:32:49 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"


int get_key(void)
{
	unsigned int key_pressed = 0;

	// read(0, &key_pressed, 1);
	// if (key_pressed == 0x1b)
	// 	read(0, ((void *)(&key_pressed)) + 1, MAX_KEY_LEN - 1);
		read(0, ((void *)(&key_pressed)) , MAX_KEY_LEN );
	return (key_pressed);
}

// void ctrl_l(t_line *line)
// {
// 	tputs(tgetstr("cl", NULL), 0, &tc_putc);
// 	ft_putstr_fd(line->prompt, 0);
// 	line->start.col = ft_strlen(line->prompt);
// 	line->start.row = 0;
// 	tputs(tgoto(tgetstr("cm", NULL), line->start.col, 0), 0, &tc_putc);
// }

void ctrl_l(t_line *line)
{
    tputs(tgetstr("cl", NULL), 0, &tc_putc);
    ft_putstr_fd(line->prompt, 0);
    line->start.col = ft_strlen(line->prompt) + 1;
    line->start.row = 0;
    ft_putstr_fd(line->cmd, 0);
    set_curpos(line);
    // tputs(tgoto(tgetstr("cm", NULL), line->start.col, 0), 0, &tc_putc);
}
void ctrl_u(t_line *line)
{
	cursor_to_home(line);
	ft_bzero(line->cmd, line->length);
	tputs(tgetstr("cd", NULL), 0, &tc_putc);
}

void match_move(int key_pressed, t_line *line)
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

void match_hist(int key_pressed, t_line *line)
{
	int i;
	static struct s_keyhist keyhist[2] = {
		{KEYCODE_U, &old_hist_entry},
		{KEYCODE_D, &new_hist_entry},
	};

	i = 0;
	while (i < 2)
		if (key_pressed == keyhist[i++].key)
			keyhist[i - 1].p(line, &(line->hist));
}