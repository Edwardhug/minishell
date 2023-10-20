/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:34:33 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 20:35:46 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_empty_env(t_exec *exec, int empty_env)
{
	if (empty_env == 1)
	{
		exec->env = ft_lstnew_env("SHLVL=1", 5);
		exec->export = ft_lstnew_env("SHLVL=1", 5);
		return (1);
	}
	return (0);
}

static char	*itoa_shlvl(t_exec *exec, char *value, int int_shlvl)
{
	free(value);
	value = ft_itoa(int_shlvl);
	if (!value)
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	return (value);
}

static int	give_shlvl_value(t_env *tmp_env, int more_or_less)
{
	int	int_shlvl;

	int_shlvl = ft_atoi(tmp_env->value);
	if (more_or_less == 1)
	{
		int_shlvl++;
		if (int_shlvl > 1000)
			int_shlvl = 0;
	}
	else
		int_shlvl--;
	return (int_shlvl);
}

void	shlvl(t_exec *exec, int empty_env, int more_or_less)
{
	t_env	*tmp_env;
	t_env	*tmp_exp;
	int		int_shlvl;

	if (is_empty_env(exec, empty_env) == 1)
		return ;
	tmp_env = exec->env;
	tmp_exp = exec->export;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->name, "SHLVL") == 0)
		{
			while (tmp_exp)
			{
				if (ft_strcmp(tmp_exp->name, "SHLVL") == 0)
					break ;
				tmp_exp = tmp_exp->next;
			}
			int_shlvl = give_shlvl_value(tmp_env, more_or_less);
			tmp_env->value = itoa_shlvl(exec, tmp_env->value, int_shlvl);
			tmp_exp->value = itoa_shlvl(exec, tmp_exp->value, int_shlvl);
			break ;
		}
		tmp_env = tmp_env->next;
	}
}
