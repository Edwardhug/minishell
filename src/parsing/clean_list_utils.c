/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:36:52 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/20 22:19:46 by jrenault         ###   ########lyon.fr   */
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

void	env_double_char(t_exec *exec, t_env_lst *str)
{
	str->tmp2 = ft_strjoin(str->tmp->name, "=");
	if (!str->tmp2)
	{
		while (str->i >= 0)
		{
			free(str->char_env[str->i]);
			str->i--;
		}
		free(str->char_env);
		free_exec_struct(exec);
		perror("malloc error\n");
		exit(EXIT_FAILURE);
	}
	str->char_env[str->i] = ft_strjoin(str->tmp2, str->tmp->value);
	if (!str->char_env[str->i])
	{
		free_tab(str->char_env);
		free_exec_struct(exec);
		perror("malloc error\n");
		exit(EXIT_FAILURE);
	}
	free(str->tmp2);
	str->tmp = str->tmp->next;
	str->i++;
}
