/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:13:13 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/21 11:17:24 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_and_write_it(t_exec *exec)
{
	ft_printf("exit\n");
	rl_clear_history();
	close(exec->fd_stand);
	free_env(exec->env);
	free_env(exec->export);
	exit(g_error_value / 256);
}
