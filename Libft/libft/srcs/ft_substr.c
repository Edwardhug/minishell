/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:42:16 by lgabet            #+#    #+#             */
/*   Updated: 2023/03/30 11:58:48 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_size_substr(size_t len, char const *s, unsigned int start)
{
	size_t	size;

	size = 0;
	if (len < ft_strlen(s) - start)
		size = len;
	else
		size = ft_strlen(s) - start;
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	if (start > ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	size = ft_size_substr(len, s, start);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	while (i < size && s[start])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
