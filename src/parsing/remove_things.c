/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:02:27 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/22 12:34:29 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_quotes(char *str)
{
	char	*ret;
	int		i;
	int		j;

	// i = 0;
	j = 0;
	// while (str[i])
	// {
	// 	if (str[i] == '"')
	// 		i++;
	// 	i++;
	// }
	i = ft_strlen(str);
	ret = calloc((i + 1), sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			i++;
		else
		{
			ret[j] = str[i];
			i++;
			j++;	
		}
	}
	return (free(str), ret);
}
