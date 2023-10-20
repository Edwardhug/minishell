/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:53:49 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 23:11:09 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_underscore_exp(t_env *tmp_exp, t_exec *exec, char *cmd)
{
	while (tmp_exp)
	{
		if (ft_strcmp(tmp_exp->name, "_") == 0)
			break ;
		tmp_exp = tmp_exp->next;
	}
	if (tmp_exp->value[0])
		free(tmp_exp->value);
	tmp_exp->value = ft_strdup(cmd);
	if (!tmp_exp->value)
	{
		free(cmd);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
}

void	change_underscore(char *cmd, t_exec *exec)
{
	t_env	*tmp_env;
	t_env	*tmp_exp;

	tmp_env = exec->env;
	tmp_exp = exec->export;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->name, "_") == 0)
		{
			change_underscore_exp(tmp_exp, exec, cmd);
			if (tmp_env->value[0] && !(ft_strcmp(cmd, "echo") == 0))
				free(tmp_env->value);
			if (!(ft_strcmp(cmd, "echo") == 0))
			{
				tmp_env->value = ft_strdup(cmd);
				if (!tmp_env->value)
				{
					free(cmd);
					free_stuff_error(exec, NULL, "malloc error\n", -1);
				}
			}
			return ;
		}
		tmp_env = tmp_env->next;
	}
}
