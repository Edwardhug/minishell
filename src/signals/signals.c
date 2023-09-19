/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:45:53 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/19 15:56:06 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// # include <stdio.h>
// # include <signal.h>
// # include <stdlib.h>

void	handle_sigint()
{
	ft_printf("\nMinishell>");
}

// void	handle_sigout(char **path)
// {
// 	free_tab(path);
// }

void	signal_main_loop()
{
	struct sigaction sig_int;
	// struct sigaction sig_out;

	sig_int.sa_handler = &handle_sigint;	//
	sig_int.sa_flags = SA_RESTART;			// pour ctrl c
	sigaction(SIGINT, &sig_int, NULL);		//
	// sig_out.sa_handler = &handle_sigout;		//
	// sig_out.sa_flags = SA_RESTART;				// pour ctrl d
	// sigaction(SIGOUT, &sig_out, NULL);			//
}