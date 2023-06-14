/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:44:20 by lgabet            #+#    #+#             */
/*   Updated: 2023/03/30 11:56:36 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_count(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			while (str[i] != c && str[i])
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

char	**ft_free(char **str, char *tamp)
{
	int	i;

	i = 0;
	while (str[i] != (NULL))
	{
		free(str[i]);
		i++;
	}
	free(str);
	free(tamp);
	return (NULL);
}

int	ft_size_split(char *str, int i, char c)
{
	int	count;

	count = 0;
	while (str[i] && str[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

char	**ft_algo(char *str, char c, char **ret, int i)
{
	int	j;
	int	k;

	k = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] != c)
		{
			ret[k] = malloc(sizeof(char) * ft_size_split(str, i, c) + 1);
			if (!ret[k])
				return (ft_free(ret, str));
			while (j < ft_size_split(str, i, c) && str[i])
			{
				ret[k][j] = str[i + j];
				j++;
			}
			i = i + j;
			ret[k++][j] = '\0';
		}
		else
			i++;
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	char	*tamp;
	int		i;
	char	set[2];

	set[0] = c;
	set[1] = '\0';
	i = 0;
	if (!s)
		return (NULL);
	tamp = ft_strtrim(s, set);
	if (!tamp)
		return (NULL);
	ret = malloc(sizeof(char *) * (ft_count(tamp, c) + 1));
	if (!ret)
	{
		free(tamp);
		return (NULL);
	}
	ret = ft_algo(tamp, c, ret, i);
	ret[ft_count(tamp, c)] = 0;
	free(tamp);
	return (ret);
}
