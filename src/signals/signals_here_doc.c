/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:25:52 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/26 19:01:04 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void sigint_handler_heredoc(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}