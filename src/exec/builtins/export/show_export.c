/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:15:34 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 16:16:48 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	ft_swap(t_env *node1, t_env *node2)
{
	char	*tmp_name;
	char	*tmp_value;

	if (node1 == NULL || node1->next == NULL)
		return ;
	if (node2 == NULL || node2->next == NULL)
		return ;
	tmp_name = node1->name;
	tmp_value = node1->value;
	node1->name = node2->name;
	node1->value = node2->value;
	node2->name = tmp_name;
	node2->value = tmp_value;
}

void	sort_list(t_exec *exec)
{
	int		swapped;
	t_env	*head;
	t_env	*last_ptr;

	last_ptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		head = exec->export;
		while (head && head->next && head->next != last_ptr)
		{
			if (ft_strcmp(head->name, head->next->name) > 0)
			{
				ft_swap(head, head->next);
				swapped = 1;
			}
			head = head->next;
		}
		last_ptr = head;
	}
}

void	show_export(t_exec *exec)
{
	t_env	*tmp;

	sort_list(exec);
	tmp = exec->export;
	while (tmp)
	{
		ft_printf("declare -x ");
		ft_printf("%s", tmp->name);
		if (tmp->value != NULL)
		{
			ft_printf("=");
			ft_printf("\"%s\"", tmp->value);
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
}
