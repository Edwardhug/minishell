/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:20:41 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/21 04:41:37 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	t_struct_strlen(t_struct *list_word)
{
	size_t		i;
	t_struct	*tmp;

	i = 0;
	tmp = list_word;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

size_t	t_env_strlen(t_env *env)
{
	size_t	i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	is_only_pipe(t_struct **temp_list)
{
	t_struct	*current;
	t_struct	*prev;

	current = *temp_list;
	prev = NULL;
	while (current)
	{
		prev = current;
		current = current->next;
	}
	while (prev)
	{
		if (prev->type == PIPE)
		{
			prev->type = ARG;
			return ;
		}
		prev = prev->next;
	}
	return ;
}
