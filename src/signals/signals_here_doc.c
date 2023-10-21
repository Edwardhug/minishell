/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:25:52 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/21 09:23:44 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler_heredoc(int sig)
{
	(void) sig;
	close(0);
	ft_putstr_fd("\n", 2);
	g_error_value = 130;
}

void	transform_utils(t_exec exec, t_struct **copy)
{
	char	*lim;

	lim = get_lim((*copy)->next->str);
	here_doc(lim, (*copy)->next->str, exec);
	free((*copy)->str);
	(*copy)->str = ft_strdup("<");
	(*copy)->type = REDIRECTION;
	(*copy) = (*copy)->next;
	free((*copy)->str);
	(*copy)->str = ft_strdup(HERE_DOC);
	(*copy)->type = FILES;
	free(lim);
}
