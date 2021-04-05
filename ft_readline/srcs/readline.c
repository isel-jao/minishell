/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:48:07 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/05 10:45:49 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		ft_getwinsz(t_winsz *winsz)
{
	winsz->col = tgetnum("co");
	winsz->row = tgetnum("li");
	return (0);
}

void	get_cursor_start_pos(t_line *line)
{
	char	answer[20];
	int		i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(answer, 20);
	i = read(0, answer, 20);
	answer[i] = 0;
	i = 2;
	line->start.row = ft_atoi(answer + i);
	while (ft_isdigit(answer[i]))
		i++;
	line->start.col = ft_atoi(answer + i + 1);
}

void	input_loop(t_line *line, int *ms_ret)
{
	int	key_pressed;

	while (42)
	{
		key_pressed = get_key();
		ft_getwinsz(&line->winsz);
		if (line->start.row + line->cursor / line->winsz.col > line->winsz.row)
			line->start.row--;
		match_move(key_pressed, line);
		match_hist(key_pressed, line);
		if (key_pressed > 31 && key_pressed < 127)
			insert_char(line, key_pressed);
		if (key_pressed == KEY_DC || key_pressed == 127)
			delete_char(line, key_pressed);
		if (key_pressed == CTRL_D && line->cmd[0] == 0 && (*line->exit = 1))
			break ;
		if (key_pressed == CTRL_C)
		{
			line->cmd[0] = 0;
			*ms_ret = 1;
			break ;
		}
		if (key_pressed == '\n')
			break ;
	}
}

void	rest_tail(t_line line)
{
	if (line.hist_depth)
	{
		while (line.hist->next)
			line.hist = line.hist->next;
		ft_lstremovenode(&line.hist);
	}
}

char	*ft_readline(char *prompt, t_list *hist, int *ms_exit, int *ms_ret)
{
	struct termios	oldattr;
	t_line			line;
	int				i;

	ft_bzero(&line, sizeof(t_line));
	ft_putstr_fd(prompt, 1);
	line.hist = hist;
	line.prompt = prompt;
	line.exit = ms_exit;
	line.hist_size = ft_lstsize(line.hist);
	setup_terminal(&oldattr);
	get_cursor_start_pos(&line);
	input_loop(&line, ms_ret);
	rest_tail(line);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	i = 0;
	while (line.cmd[i] == ' ')
		i++;
	return (ft_strdup(&line.cmd[i]));
}
