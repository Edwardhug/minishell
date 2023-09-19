/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:03:02 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/19 11:43:33 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_list(t_struct **lst)
{
	t_struct	*tamp;

	if (lst && *lst)
	{
		while (*lst)
		{
			tamp = *lst;
			free((*lst)->str);
			*lst = tamp->next;
			free(tamp);
		}
		*lst = NULL;
	}
}