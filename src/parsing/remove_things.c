/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:02:27 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/09 12:24:41 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*have_dollar_sign(char *str, char *ret, int *i, int *j)
{
	if (str[*i] == '"' && str[(*i) - 1] == '$')
	{
		(*i)++;
		while (str[*i] != '"')
		{
			ret[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
	}
	return (ret);
}

char	*remove_simple_quotes(char *str)
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(str);
	ret = calloc((i + 1), sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (str[i + 1] == '$'))
			return (free(ret), str);
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

	j = 0;
	i = ft_strlen(str);
	ret = calloc((i + 1), sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			ret = have_dollar_sign(str, ret, &i, &j);
			i++;
		}
		else
		{
			ret[j] = str[i];
			i++;
			j++;
		}
	}
	return (free(str), remove_simple_quotes(ret));
}
