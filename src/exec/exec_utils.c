/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 22:07:38 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 22:07:39 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error(char **splited_cmd, char **all_path, int i)
{
	if (i == 1)
		ft_putstr_err("command not found: ");
	else
		ft_putstr_err("no such file or directory: ");
	ft_putstr_err(splited_cmd[0]);
	ft_putstr_err("\n");
	free_tab(all_path);
}

void	change_outfile(t_struct **temp_list, int *fd)
{
	if (!ft_strcmp((*temp_list)->str, ">>"))
	{
		(*temp_list) = (*temp_list)->next;
		(*fd) = open((*temp_list)->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (!ft_strcmp((*temp_list)->str, ">"))
	{
		(*temp_list) = (*temp_list)->next;
		(*fd) = open((*temp_list)->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
}
