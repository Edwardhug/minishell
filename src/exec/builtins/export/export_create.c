/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:45:34 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 16:47:43 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

t_env	*create_new_exp(t_exec *exec, t_env *head, t_env *args_tmp)
{
	t_env	*new_exp;

	new_exp = ft_lstnew_export(args_tmp);
	if (!new_exp)
	{
		free_env(head);
		free_exec_struct(exec);
		exit(EXIT_FAILURE);
	}
	if (new_exp->value)
		free(new_exp->value);
	new_exp->value = NULL;
	new_exp->next = exec->export;
	exec->export = new_exp;
	return (new_exp);
}

void	create_var(t_env *args_tmp, t_exec *exec, t_env *head)
{
	t_env	*new_exp;
	t_env	*new_env;

	if (args_tmp->value == NULL || args_tmp->value[0] == '\0')
		new_exp = create_new_exp(exec, head, args_tmp);
	else
	{
		new_exp = ft_lstnew_export(args_tmp);
		if (!new_exp)
		{
			free_env(head);
			free_stuff_error(exec, NULL, "malloc error\n", -1);
		}
		new_exp->next = exec->export;
		exec->export = new_exp;
		new_env = ft_lstnew_export(args_tmp);
		if (!new_env)
		{
			free_env(head);
			free_stuff_error(exec, NULL, "malloc error\n", -1);
		}
		new_env->next = exec->env;
		exec->env = new_env;
	}
}
