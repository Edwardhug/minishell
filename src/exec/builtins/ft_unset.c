/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:24:31 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 17:24:38 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_lstdelete_node(t_exec *exec, t_env *node_to_delete, int boolean)
{
	t_env	*previous;
	t_env	*current;

	previous = NULL;
	if (boolean == 1)
		current = exec->env;
	else
		current = exec->export;
	while (current)
	{
		if (current == node_to_delete)
		{
			if (previous)
			{
				previous->next = current->next;
			}
			else
			{
				if (boolean == 1)
					exec->env = current->next;
				else
					exec->export = current->next;
			}
			free(current->name);
			free(current->value);
			free(current);
			break ;
		}
		previous = current;
		current = current->next;
	}
}

int	ft_unset(char **cmd, t_exec *exec)
{
	t_env	*tmp_env;
	t_env	*tmp_exp;
	int		i;

	i = 1;
	while (cmd[i])
	{
		tmp_env = exec->env;
		tmp_exp = exec->export;
		while (tmp_env)
		{
			if (ft_strcmp(cmd[i], tmp_env->name) == 0)
			{
				while (tmp_exp)
				{
					if (ft_strcmp(cmd[i], tmp_exp->name) == 0)
					{
						ft_lstdelete_node(exec, tmp_exp, 0);
						break ;
					}
					tmp_exp = tmp_exp->next;
				}
				ft_lstdelete_node(exec, tmp_env, 1);
				break ;
			}
			tmp_env = tmp_env->next;
		}
		i++;
	}
	if (exec->nb_cmds > 1)
	{
		free_tab(cmd);
		free_exec_fork(exec);
		exit(0);
	}
	g_error_value = -77;
	return (0);
}
