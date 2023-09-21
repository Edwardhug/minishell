/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:13:13 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/21 11:13:15 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exit_and_write_it(char **path)
{
	ft_printf("exit\n");
	rl_clear_history();
	free_tab(path);
	exit(EXIT_SUCCESS);				// verifier si c'est bien exit success
}