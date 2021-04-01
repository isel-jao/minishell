/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 22:17:32 by isel-jao          #+#    #+#             */
/*   Updated: 2021/03/16 17:45:43 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void sig_int(int code)
{
    (void)code;
    ft_putstr_fd("\n", STDERR);
    g_sig.exit_status = 130;
}

void sig_quit(int code)
{
    ft_putstr_fd("Quit: 3\n", STDERR);
    g_sig.exit_status = 131;
}

void sig_init(void)
{
    g_sig.pid = 0;
    g_sig.exit_status = 0;
}
