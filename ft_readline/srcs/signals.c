/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:07:02 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/16 17:07:39 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void sig_int(int code)
{
    (void)code;
    if (g_sig.pid == 0)
    {
        // // ft_putstr_fd("\b\b  \n", STDERR);
        // ft_prompt(1);
        g_sig.exit_status = 1;
    }
    else
    {
        // ft_putstr_fd("\n", STDERR);
        g_sig.exit_status = 130;
    }
}

void sig_quit(int code)
{
    char *nbr;
    if (g_sig.pid != 0)
    {
        ft_putstr_fd("Quit: 3\n", 2);
        g_sig.exit_status = 131;
    }

}

void sig_init(void)
{
    g_sig.pid = 0;
    g_sig.exit_status = 0;
}
