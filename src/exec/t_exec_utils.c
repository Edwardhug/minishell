/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:06:20 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/21 20:11:18 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error(char **splited_cmd, char **all_path, int i)
{
	if (i == 1)
		ft_putstr_fd("command not found: ", 2);
	else
		ft_putstr_fd("no such file or directory: ", 2);
	ft_putstr_fd(splited_cmd[0], 2);
	ft_putstr_fd("\n", 2);
	free_tab(splited_cmd);
	free_tab(all_path);
}