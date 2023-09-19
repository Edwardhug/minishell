/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lezard <lezard@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:51:21 by lezard            #+#    #+#             */
/*   Updated: 2023/09/19 13:32:35 by lezard           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_cd(t_exec *exec, t_struct *temp_word)
{
	t_struct	*tmp;

	(void)exec;
	printf("on entre dans ft_cd\n");
	tmp = temp_word;
	while (tmp->type != ARG) //on cherche le premier argument qui est en théorie le chemin où on veut aller.
	{
		tmp = tmp->next;
	}
	chdir(tmp->str);
	return (0);
}
/*
getcwd
chdir
faire gaffe à "cd -" et "cd ~" + "cd"
d'autres cas spéciaux mais osef
*/