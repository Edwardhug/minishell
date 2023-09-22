/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:51:21 by lezard            #+#    #+#             */
/*   Updated: 2023/09/22 11:34:56 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_cd(char **cmd)
{
	chdir(cmd[1]);
	return (0);
}
/*
getcwd
chdir
faire gaffe à "cd -" et "cd ~" + "cd"
d'autres cas spéciaux mais osef
*/