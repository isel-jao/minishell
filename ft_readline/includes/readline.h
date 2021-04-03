/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:49:07 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/03 10:59:41 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "../../libft/includes/libft.h"
# include <termcap.h>
# include <term.h>
# include <termios.h>
# include <curses.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/ioctl.h>

# define MAX_CMD_LEN 4096
# define MAX_KEY_LEN 4

# define HISTORY_PATH ".ms_history"

# define KEYCODE_R 0x435b1b
# define KEYCODE_L 0x445b1b
# define KEYCODE_U 0x415b1b
# define KEYCODE_D 0x425b1b
# define KEYCODE_HOME 0x485b1b
# define KEYCODE_END 0x465b1b
# define KEYCODE_DEL 0x7e335b1b

# define KEYCODE_Q 0x71

# define CTRL_U 0x15
# define CTRL_L 0xc
# define CTRL_D 0x4
# define CTRL_C 0x3

typedef struct		s_keymatch
{
	char			*key_code;
	int				key_ret;
}					t_keymatch;

int get_key(void);

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct		s_winsz
{
	size_t			row;
	size_t			col;
}					t_winsz;

typedef struct		s_line
{
	int				*exit;
	t_list			*hist;
	size_t			cursor;
	size_t			length;
	size_t			hist_depth;
	size_t			hist_size;
	t_winsz			winsz;
	t_winsz			start;
	char			*prompt;
	char			cmd[MAX_CMD_LEN];
}					t_line;

int					tc_putc(int c);

char				*ft_readline(char *prompt, t_list *hist, int *ms_exit, \
int *ms_ret);

/*
** terminal setup
*/

void				fatal(char *error);
void				init_terminal_data();
void				setup_terminal(struct termios *oldattr);

/*
** cursor motions
*/

void				cursor_to_end(t_line *line);
void				cursor_to_home(t_line *line);
void				cursor_to_left(t_line *line);
void				cursor_to_right(t_line *line);
void				set_curpos(t_line *line);

/*
** history
*/

void				ft_lstadd(t_list **head, t_list *new);
t_list				*ft_lstadd_back(t_list **list, t_list *new);
t_list				*ft_lstnew(void			*content);
t_list				*retrieve_history(int *h_fd);
int					ft_lstsize(t_list *tail);
void				appand_history(char *line, int h_fd);
void				ft_lstremovenode(t_list **hist);
void				print_history(t_list *hist);

void				new_hist_entry(t_line *line, t_list **hist);
void				old_hist_entry(t_line *line, t_list **hist);

/*
** input
*/

void				insert_char(t_line *line, int key);
void				delete_char(t_line *line, int key);

/*
** key
*/

int					get_key(void);
void				match_move(int key_pressed, t_line *line);
void				match_hist(int key_pressed, t_line *line);

/*
** signals
*/

void				sig_init(void);
void				sig_quit(int code);
void				sig_int(int code);

#endif
