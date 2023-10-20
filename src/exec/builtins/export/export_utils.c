/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:55:54 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 13:56:25 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	failure_tmp_value(t_exec *exec, t_env *head, int what)
{
	if (what == 0)
		perror("tmp_env->value malloc\n");
	else
		perror("tmp_exp->value dup error\n");
	free_exec_struct(exec);
	if (head)
		free_env(head);
	exit(EXIT_FAILURE);
}
