/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lezard <lezard@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:52:22 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/18 16:09:04 by lezard           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_struct	*new_node(char *content, t_enum type)
{
	t_struct	*node;

	node = (t_struct *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->str = content;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	add_node_back(t_struct **list, t_struct *new_node)
{
	t_struct	*last;

	if (list)
	{
		if (*list)
		{
			last = get_last_node(*list);
			last->next = new_node;
		}
		else
			*list = new_node;
	}
}

t_struct	*get_last_node(t_struct *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	delete_node(t_struct **lst)
{
	t_struct	*tmp;

	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp->str);
	tmp->str = NULL;
	free(tmp);
}
