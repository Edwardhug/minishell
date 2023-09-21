/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:13:13 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/21 22:55:26 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exit_and_write_it(char **path, int fd_standart)
{
	ft_printf("exit\n");
	rl_clear_history();
	free_tab(path);
	close(fd_standart);
	(void)fd_standart;
	exit(EXIT_SUCCESS);				// verifier si c'est bien exit success
}
