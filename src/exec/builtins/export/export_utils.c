/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:55:54 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 15:24:46 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

t_env	*dup_existing_value(t_exec *exec, t_env *head,
	t_env *tmp_exp, t_env *args_tmp)
{
	if (tmp_exp->value)
		free(tmp_exp->value);
	tmp_exp->value = ft_strdup(args_tmp->value);
	if (!tmp_exp->value)
		failure_tmp_value(exec, head, 1);
	return (tmp_exp);
}

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

t_env	*deal_not_in_env(t_exec *exec, t_env *tmp_env,
	t_env *head, t_env *args_tmp)
{
	tmp_env = ft_lstnew_export(args_tmp);
	if (!tmp_env)
	{
		if (head)
			free_env(head);
		free_exec_struct(exec);
		exit(EXIT_FAILURE);
	}
	tmp_env->next = exec->env;
	exec->env = tmp_env;
	return (tmp_env);
}

t_env	*find_env_for_export(t_env *tmp_env, t_env *args_tmp,
	t_exec *exec, t_env *head)
{
	if (tmp_env->value)
		free(tmp_env->value);
	tmp_env->value = ft_strdup(args_tmp->value);
	if (!tmp_env->value)
		failure_tmp_value(exec, head, 0);
	return (tmp_env);
}
