/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:45:13 by isel-jao          #+#    #+#             */
/*   Updated: 2021/04/02 13:36:36 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	fatal(char *error)
{
	ft_putstr(error);
	exit(0);
}

void	init_terminal_data(void)
{
	char	*term_buffer;
	char	*termtype;
	int		success;

	term_buffer = NULL;
	termtype = getenv("TERM");
	if (termtype == 0)
		fatal("Specify a terminal type with `setenv TERM <yourtype>'.\n");
	success = tgetent(term_buffer, termtype);
	if (success < 0)
		fatal("Could not access the termcap data base.\n");
	if (success == 0)
		fatal("Terminal type `%s' is not defined.\n");
}

void	setup_terminal(struct termios *oldattr)
{
	struct termios	newattr;

	tcgetattr(STDIN_FILENO, oldattr);
	newattr = *oldattr;
	newattr.c_lflag &= ~(ISIG | ICANON | ECHO);
	init_terminal_data();
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
}
