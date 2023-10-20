/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:24:31 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 18:17:23 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	free_current(t_env *current)
{
	free(current->name);
	free(current->value);
	free(current);
}

static void	ft_lstdelete_node(t_exec *exec, t_env *node_to_delete,
	int boolean, t_env *previous)
{
	t_env	*current;

	if (boolean == 1)
		current = exec->env;
	else
		current = exec->export;
	while (current)
	{
		if (current == node_to_delete)
		{
			if (previous)
				previous->next = current->next;
			else
			{
				if (boolean == 1)
					exec->env = current->next;
				else
					exec->export = current->next;
			}
			free_current(current);
			break ;
		}
		previous = current;
		current = current->next;
	}
}

static void	delete_exp(t_exec *exec, t_env *tmp_exp, char **cmd, int i)
{
	while (tmp_exp)
	{
		if (ft_strcmp(cmd[i], tmp_exp->name) == 0)
		{
			ft_lstdelete_node(exec, tmp_exp, 0, NULL);
			break ;
		}
		tmp_exp = tmp_exp->next;
	}
}

void	unset_if_pipe(t_exec *exec, char **cmd)
{
	if (exec->nb_cmds > 1)
	{
		free_tab(cmd);
		free_exec_fork(exec);
		exit(0);
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
				delete_exp(exec, tmp_exp, cmd, i);
				ft_lstdelete_node(exec, tmp_env, 1, NULL);
				break ;
			}
			tmp_env = tmp_env->next;
		}
		i++;
	}
	unset_if_pipe(exec, cmd);
	g_error_value = -77;
	return (0);
}
