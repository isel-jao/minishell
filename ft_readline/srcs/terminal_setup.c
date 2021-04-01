/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:45:13 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/16 17:18:13 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void fatal(char *error, char *termtype)
{
	ft_putstr(error);
	ft_putstr(error);
	exit(0);
}

void init_terminal_data()
{
	char *term_buffer;
	char *termtype = getenv("TERM");
	int success;
	if (termtype == 0)
		fatal("Specify a terminal type with `setenv TERM <yourtype>'.\n", termtype);

	success = tgetent(term_buffer, termtype);
	if (success < 0)
		fatal("Could not access the termcap data base.\n", termtype);
	if (success == 0)
		fatal("Terminal type `%s' is not defined.\n", termtype);
}

void setup_terminal(struct termios *oldattr)
{
	struct termios newattr;
	tcgetattr(STDIN_FILENO, oldattr);
	newattr = *oldattr;
	newattr.c_lflag &= ~( ISIG | ICANON | ECHO);
	// newattr.c_lflag &= ~(ICANON | ECHO | ISIG);
	// newattr.c_oflag &= ~(OPOST);
	init_terminal_data();
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
}