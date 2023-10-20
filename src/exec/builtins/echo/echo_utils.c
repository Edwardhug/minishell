/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:57:36 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 23:10:56 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int	is_dash_n(char *arg)
{
	int	i;

	i = 1;
	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

int	dash_n_handling(int *dash_n, int *newline, int *i, char **cmd)
{
	*newline = 0;
	while (cmd[*i])
	{
		*dash_n = is_dash_n(cmd[*i]);
		if (!(*dash_n))
		{
			(*newline)++;
			(*i)++;
		}
		else
			break ;
	}
	return (0);
}
