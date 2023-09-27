/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:02:27 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/27 14:19:07 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_simple_quotes(char *str)
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
		if (str[i] == '\'')
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
	return (free(str), remove_simple_quotes(ret));
}
