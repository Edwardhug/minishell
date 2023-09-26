/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:45:53 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/26 12:43:46 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// # include <stdio.h>
// # include <signal.h>
// # include <stdlib.h>

void	handle_sigint_main_loop(int signal)
{
	if (signal == SIGINT)
		ft_printf("\nMinishell>");
}

// void	signal_main_loop()
// {
// 	struct sigaction sig_int;

// 	sig_int.sa_handler = &handle_sigint_main_loop;	//
// 	sig_int.sa_flags = SA_RESTART;					// pour ctrl c
// 	sigaction(SIGINT, &sig_int, NULL);				//
// 	signal(SIGQUIT, SIG_IGN);			// pour ctrl backslash
// }

void	no_line_return(int sig)
{
	(void) sig;
}

void	sigquit_handler_in_process(int sig)
{
	sig_t	old_signal;

	old_signal = signal(SIGINT, no_line_return);
	(void) sig;
	kill(0, SIGINT);
	signal(SIGINT, old_signal);
}

void	sigint_handler_in_process(int sig)
{
	(void) sig;
	ft_printf("\n");
}

void	sigint_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}