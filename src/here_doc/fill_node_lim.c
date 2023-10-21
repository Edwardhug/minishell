/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node_lim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:47:03 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/21 03:58:49 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_lim(char *line, int *i, t_exec *exec)
{
	int		j;
	int		k;
	char	*ret;

	j = 0;
	k = 0;
	while (line[j + (*i)] && line[j + (*i)] != ' ')
		j++;
	ret = ft_calloc(j + 1, sizeof(char));
	if (!ret)
		return (free_stuff_error(exec, NULL, "Malloc error\n", -1), NULL);
	while (k != j)
	{
		ret[k] = line[(*i) + k];
		k++;
	}
	(*i) = (*i) + k;
	return (ret);
}
