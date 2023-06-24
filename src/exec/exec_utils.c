/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:59:53 by jrenault          #+#    #+#             */
/*   Updated: 2023/06/24 18:04:51 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**take_full_cmd(t_struct *lst)
{
	char		**args;
	t_struct	*tmp;

	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
	}
	return (args);
}

int	what_exec(t_struct *lst)
{
	t_struct	*tmp;
	int			nb;

	nb = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->type == PIPE)
			nb++;
		tmp = tmp->next;
	}
	return (nb);
}
