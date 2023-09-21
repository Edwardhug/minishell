/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:51:21 by lezard            #+#    #+#             */
/*   Updated: 2023/09/20 17:44:58 by codespace        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_cd(t_exec *exec)
{
	chdir(exec->cmd[1]);
	return (0);
}
/*
getcwd
chdir
faire gaffe à "cd -" et "cd ~" + "cd"
d'autres cas spéciaux mais osef
*/