/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:03:31 by lgabet            #+#    #+#             */
/*   Updated: 2023/03/30 11:56:36 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*s2;
	char	*r;
	int		i;

	s2 = (char *)s1;
	len = ft_strlen(s2);
	i = 0;
	r = malloc (sizeof(char) * len + 1);
	if (!r)
		return (NULL);
	if (len == 0)
	{
		r[0] = '\0';
		return (r);
	}
	while (i < len)
	{
		r[i] = s2[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
