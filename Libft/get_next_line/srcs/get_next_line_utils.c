/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:44:03 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/03 16:28:14 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;

	len_s1 = ft_strlen_gnl(s1);
	len_s2 = ft_strlen_buff(s2);
	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (++i < len_s1)
		str[i] = s1[i];
	while (j < len_s2)
		str[i++] = s2[j++];
	str[len_s1 + len_s2] = 0;
	free(s1);
	return (str);
}

int	ft_strlen_buff(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

int	have_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen_gnl(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
