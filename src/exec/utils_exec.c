/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 22:07:59 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/21 09:14:37 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_value_utils(int *status)
{
	if (g_error_value == -77)
		(*status) = 0;
	else if (g_error_value == -130)
		(*status) = 130 * 256;
	else if (g_error_value == -131)
		(*status) = 131 * 256;
}

void	change_value_builtin(t_struct *list_word, t_exec *exec, int *status)
{
	while (list_word)
	{
		if ((ft_strcmp(list_word->str, "cd") == 0)
			|| (ft_strcmp(list_word->str, "export") == 0
				&& exec->nb_cmds == 1)
			|| (ft_strcmp(list_word->str, "exit") == 0))
		{
			if (g_error_value == -1)
				(*status) = 256;
			else
				(*status) = 0;
		}
		else if (ft_strcmp(list_word->str, "pwd") == 0)
		{
			if (g_error_value == -127)
				(*status) = 127 * 256;
			else
				(*status) = 0;
		}
		change_value_utils(status);
		list_word = list_word->next;
	}
}

int	to_next_cmd(t_struct **temp_list)
{
	while ((*temp_list)->next && (*temp_list)->type != PIPE)
	{
		(*temp_list) = (*temp_list)->next;
	}
	if ((*temp_list)->type == PIPE)
	{
		(*temp_list) = (*temp_list)->next;
		return (0);
	}
	else
		return (1);
}
