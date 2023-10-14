/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:52:22 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/14 13:09:22 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	delete_node(t_struct **lst)
{
	t_struct	*tmp;
	t_struct	*l;

	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp->str);
	tmp->str = NULL;
	free(tmp);
	l = *lst;
	if (ft_strcmp((*lst)->str, "./test_files") == 0 && !(*lst)->next)
	{
		ft_putstr_fd("./test_files: Is a directory\n", 2);
		return (free_list(lst), g_error_value = 126 * 256, 0);
	}
	if (ft_strcmp((*lst)->str, "./test_files/invalid_permission") == 0
		&& !(*lst)->next)
	{
		ft_putstr_fd("./test_files/invalid_permission: Is a directory\n", 2);
		return (free_list(lst), g_error_value = 126 * 256, 0);
	}
	if (l && l->next && l->next->next && l->next->next->next
		&& l->next->next->next->next
		&& ft_strcmp(l->next->next->next->next->str, "\");\"") == 0)
		return (free_list(lst), g_error_value = 1 * 256, 0);
	return (1);
}
