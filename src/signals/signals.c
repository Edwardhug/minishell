/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:45:53 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/19 16:51:09 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// # include <stdio.h>
// # include <signal.h>
// # include <stdlib.h>

void	handle_sigint_main_loop()
{
	ft_printf("\nMinishell>");
}

void	handle_sigout()
{
}

void	signal_main_loop()
{
	struct sigaction sig_int;

	sig_int.sa_handler = &handle_sigint_main_loop;	//
	sig_int.sa_flags = SA_RESTART;					// pour ctrl c
	sigaction(SIGINT, &sig_int, NULL);				//
	signal(SIGQUIT, SIG_IGN);			// pour ctrl backslash
}