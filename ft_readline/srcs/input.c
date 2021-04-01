/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 00:59:03 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/18 11:33:31 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int tc_putc(int c)
{
  return (write(0, &c, 1));
}

void insert_char(t_line *line, int key)
{
  if (line->length + 1 >= MAX_CMD_LEN)
    return;
  ft_memmove(line->cmd + line->cursor + 1, line->cmd + line->cursor,
             MAX_CMD_LEN - line->cursor - 1);
  line->cmd[line->cursor] = key;
  line->length++;
  line->cursor++;
  // tputs(tgetstr("im", NULL), 1, &tc_putc);
  // ft_putchar_fd(key, 0);
  // tputs(tgetstr("ei", NULL), 1, &tc_putc);
  tputs(tgetstr("cd", NULL), 0, &tc_putc);
  ft_putstr_fd(line->cmd + line->cursor - 1, 0);
  set_curpos(line);
}

void delete_char(t_line *line, int key)
{
  if (key == 127 && !line->cursor)
    return;
  if (key == 127)
    cursor_to_left(line);
  if (line->cursor == line->length)
    return;
  ft_memmove(line->cmd + line->cursor, line->cmd + line->cursor + 1,
             MAX_CMD_LEN - line->cursor - 1);
  line->length--;
  tputs(tgetstr("cd", NULL), 0, &tc_putc);
  ft_putstr_fd(line->cmd + line->cursor, 0);
  set_curpos(line);
}