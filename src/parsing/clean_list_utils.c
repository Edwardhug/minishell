/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:36:52 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/20 20:37:36 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	switch_loop(t_struct **list, t_exec exec)
{
	char		*value;

	if ((*list)->str && ft_strcmp((*list)->str, "echo") == 0
		&& ft_strcmp((*list)->next->str + 1, exec.env->name) == 0)
	{
		value = dup_without_space(exec.env->value);
		if (!value)
			return (1);
		free((*list)->next->str);
		(*list)->next->str = NULL;
		(*list)->next->str = value;
		return (1);
	}
	else if (ft_strcmp((*list)->next->str + 1, exec.env->name) == 0)
	{
		value = ft_strdup(exec.env->value);
		if (!value)
			return (1);
		free((*list)->next->str);
		(*list)->next->str = NULL;
		(*list)->next->str = value;
		return (1);
	}
	return (0);
}

void	clear_underscore(t_exec *exec)
{
	exec->env->next = ft_lstnew_env("_=", 1);
	exec->export->next = ft_lstnew_env("_=", 1);
}
