/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:39:14 by lgabet            #+#    #+#             */
/*   Updated: 2023/03/30 11:56:36 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			sl;
	size_t			dl;
	unsigned int	i;
	char			*s;

	i = 0;
	s = (char *)src;
	dl = ft_strlen(dst);
	sl = ft_strlen(s);
	if (dstsize <= 0)
		return (sl);
	if (dstsize < dl)
		return (dstsize + sl);
	while (i < sl && dl + i < dstsize - 1)
	{
		dst[i + dl] = src[i];
		i++;
	}
	dst[i + dl] = '\0';
	return (dl + sl);
}
