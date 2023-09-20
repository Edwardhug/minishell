/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:33:06 by jrenault          #+#    #+#             */
/*   Updated: 2023/09/20 13:02:22 by codespace        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	size;

	if (!haystack && !len)
		return (NULL);
	size = ft_strlen((needle));
	i = 0;
	j = 0;
	while (haystack[i] && j < size && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j])
			j++;
		i++;
	}
	if (!(needle[0]))
		return (((char *)haystack));
	if (i + j - 1 > len)
		return (NULL);
	if (j == size)
		return (&((char *)haystack)[i - 1]);
	return (0);
}
