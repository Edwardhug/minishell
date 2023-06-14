/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:35:33 by lgabet            #+#    #+#             */
/*   Updated: 2023/03/30 11:56:36 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	char		*s;
	char		*n;

	i = 0;
	s = (char *)haystack;
	n = (char *)needle;
	if (n[i] == '\0')
		return (s);
	while (s[i] && i <= len && len != 0)
	{
		j = 0;
		while (s[i + j] == n[j] && i + j < len)
		{
			if (n[j + 1] == '\0')
				return (&s[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
