/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_last_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:15:29 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/22 19:17:56 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_last_cmd(t_struct *temp_list, char **env)
{
	if (is_builtin(t_get_clean_cmd(temp_list)))
		return ;
	t_change_stdout(temp_list, 1);
	t_apply_exec(temp_list, env);
	exit(EXIT_FAILURE);
}