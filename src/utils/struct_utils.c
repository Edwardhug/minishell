/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_struct_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:20:41 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/29 09:48:08 by lgabet           ###   ########.fr       */
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
