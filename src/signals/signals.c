/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:45:53 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/21 03:17:26 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	no_line_return(int sig)
{
	(void) sig;
}

void	sigquit_handler_in_process(int sig)
{
	ft_putstr_fd("Quit (core dumped)", 2);
	(void) sig;
	kill(0, SIGINT);
	g_error_value = -131;
}

void	sigint_handler_in_process(int sig)
{
	(void) sig;
	g_error_value = -130;
	ft_printf("\n");
}

void	sigint_handler(int sig)
{
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_error_value = 130 * 256;
	(void) sig;
}

void	signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
