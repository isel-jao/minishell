/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao  <isel-jao@student.42.f>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:49:07 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/17 13:00:11 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
#define READLINE_H

#include "../../libft/includes/libft.h"
#include <termcap.h>
#include <term.h>
#include <termios.h>
#include <curses.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/ioctl.h>

#define MAX_CMD_LEN 4096
#define MAX_KEY_LEN 4

#define HISTORY_PATH ".ms_history"

#define KEY_CODE_UP "\x1b\x5b\x41\0"
#define KEY_CODE_DO "\x1b\x5b\x42\0"
#define KEY_CODE_RI "\x1b\x5b\x43\0"
#define KEY_CODE_LE "\x1b\x5b\x44\0"

#define KEY_CODE_DEL "\x1b\x5b\x33\x7e"

// # define KEY_CODE_HOME "\x1b\x5b\x48\0"
// # define KEY_CODE_END "\x1b\x5b\x46\0"

// #define KEY_CODE_SUP "\x1b\x1b\x5b\x41"
// #define KEY_CODE_SDO "\x1b\x1b\x5b\x42"
// #define KEY_CODE_SRI "\x1b\x1b\x5b\x43"
// #define KEY_CODE_SLE "\x1b\x1b\x5b\x44"


#define KEYCODE_R 0x435b1b // Left Arrow Key
#define KEYCODE_L 0x445b1b // Right Arrow Key
#define KEYCODE_U 0x415b1b // Up Arrow Key
#define KEYCODE_D 0x425b1b // Down Arrow Key
#define KEYCODE_HOME 0x485b1b
#define KEYCODE_END 0x465b1b
#define KEYCODE_DEL 0x7e335b1b
// #define KEYCODE_DEL "\x1b\x5b\x33\x7e"

#define KEYCODE_Q 0x71 // Q Key

#define CTRL_U 0x15
#define CTRL_L 0xc
#define CTRL_D 0x4
#define CTRL_C 0x3

typedef struct s_keymatch
{
	char *key_code;
	int key_ret;
} t_keymatch;

int get_key(void);

typedef struct s_list
{
	void *content;
	struct s_list *next;
	struct s_list *prev;
} t_list;

typedef struct s_winsz
{
	size_t row;
	size_t col;
} t_winsz;

typedef struct s_line
{
	t_list *hist;
	char *prompt;
	int	*exit;
	size_t cursor;
	size_t length;
	size_t hist_depth;
	size_t hist_size;
	t_winsz winsz;
	t_winsz start;
	char cmd[MAX_CMD_LEN];
} t_line;

struct s_keymove
{
	int key;
	void (*p)(t_line *line);
};

struct s_keyhist
{
	int key;
	void (*p)(t_line *line, t_list **hist);
};



int tc_putc(int c);


char *ft_readline(char *prompt, t_list *hist, int *ms_exit, int *ms_ret);


// terminal setup

void fatal(char *error, char *termtype);
void init_terminal_data();
void setup_terminal(struct termios *oldattr);

// cursor motions
void cursor_to_end(t_line *line);
void cursor_to_home(t_line *line);
void cursor_to_left(t_line *line);
void cursor_to_right(t_line *line);
void set_curpos(t_line *line);

// history
void ft_lstadd(t_list **head, t_list *new);
t_list *ft_lstadd_back(t_list **list, t_list *new);
t_list *ft_lstnew(void *content);
t_list *retrieve_history(int *h_fd);
int ft_lstsize(t_list *tail);
void appand_history(char *line, int h_fd);
void ft_lstremovenode(t_list **hist);
void print_history(t_list *hist);
static void feed_line(t_line *line, char *entry);
void new_hist_entry(t_line *line, t_list **hist);
void old_hist_entry(t_line *line, t_list **hist);

// input

void insert_char(t_line *line, int key);
void delete_char(t_line *line, int key);

// key
int get_key(void);
void match_move(int key_pressed, t_line *line);
void match_hist(int key_pressed, t_line *line);

// signals
void sig_init(void);
void sig_quit(int code);
void sig_int(int code);


#endif