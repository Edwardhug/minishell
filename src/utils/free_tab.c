/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:03:02 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/14 13:28:02 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_list(t_struct **lst)
{
	t_struct	*temp;

	if (lst && *lst)
	{
		while (*lst)
		{
			temp = *lst;
			free((*lst)->str);
			*lst = temp->next;
			free(temp);
		}
		*lst = NULL;
	}
}

void	free_env(t_env *lst)
{
	t_env	*temp;

	if (lst)
	{
		while (lst)
		{
			temp = lst;
			free(lst->name);
			if (lst->value)
				free(lst->value);
			lst = temp->next;
			free(temp);
		}
		lst = NULL;
	}
}
