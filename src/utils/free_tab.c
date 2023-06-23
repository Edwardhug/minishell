/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:03:02 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/23 15:33:50 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
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
