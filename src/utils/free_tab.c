/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lezard <lezard@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:03:02 by lgabet            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/19 11:43:33 by lgabet           ###   ########.fr       */
=======
/*   Updated: 2023/09/18 16:13:51 by lezard           ###   ########lyon.fr   */
>>>>>>> origin/exec
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	free_tab(char **tab)
// {
// 	int	i;

<<<<<<< HEAD
	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
=======
// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }
>>>>>>> origin/exec

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
