/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:02:27 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/14 13:04:36 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*have_dollar_sign(char *str, char *ret, int *i, int *j)
{
	if (str[(*i) + 1] && str[*i + 1] == '"' && str[(*i)] == '$')
	{
		(*i)++;
		while (str[*i] && str[*i] != '"')
		{
			ret[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
	}
	return (ret);
}

char	*remove_simple_quotes(char *str, t_exec *exec)
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(str);
	ret = ft_calloc((i + 1), sizeof(char));
	if (!ret)
	{
		free(str);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
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

char	*remove_quotes(char *str, t_exec *exec)
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(str);
	ret = ft_calloc((i + 2), sizeof(char));
	if (!ret)
	{
		free(str);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
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
	return (free(str), remove_simple_quotes(ret, exec));
}
