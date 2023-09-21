/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/signals/signals.c
/*   Created: 2023/09/19 14:45:53 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/19 17:11:45 by lgabet           ###   ########.fr       */
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

void	signal_main_loop()
{
	struct sigaction sig_int;

	sig_int.sa_handler = &handle_sigint_main_loop;	//
	sig_int.sa_flags = SA_RESTART;					// pour ctrl c
	sigaction(SIGINT, &sig_int, NULL);				//
	signal(SIGQUIT, SIG_IGN);			// pour ctrl backslash
}
=======
/*   Created: 2022/11/08 10:26:49 by jrenault          #+#    #+#             */
/*   Updated: 2022/11/15 11:42:52 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	int	len;

	len = ft_strlen((string));
	while (len >= 0)
	{
		if (string[len] == ((char)searchedChar))
			return (&((char *)string)[len]);
		len--;
	}
	return (0);
}
>>>>>>> origin/exec:libft/ft_strrchr.c
