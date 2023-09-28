/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_struct_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lezard <lezard@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:20:41 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/19 14:38:10 by lezard           ###   ########lyon.fr   */
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

