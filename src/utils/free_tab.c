/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:03:02 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/29 09:48:08 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	free_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }

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
