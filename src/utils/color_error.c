/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 12:00:00 by lgabet            #+#    #+#             */
/*   Updated: 2026/10/11 12:00:00 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_putstr_err(char *s)
{
	if (!s)
		return ;
	if (isatty(STDERR_FILENO))
		ft_putstr_fd(ERR_COLOR, 2);
	ft_putstr_fd(s, 2);
	if (isatty(STDERR_FILENO))
		ft_putstr_fd(ERR_RESET, 2);
}

void	ft_perror_err(char *s)
{
	if (isatty(STDERR_FILENO))
		ft_putstr_fd(ERR_COLOR, 2);
	perror(s);
	if (isatty(STDERR_FILENO))
		ft_putstr_fd(ERR_RESET, 2);
}
