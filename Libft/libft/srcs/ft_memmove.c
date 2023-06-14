/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:48:50 by lgabet            #+#    #+#             */
/*   Updated: 2023/03/30 11:56:36 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*cdst;
	const char	*csrc;

	cdst = dst;
	csrc = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst < src)
	{
		while (n--)
		{
			*cdst = *csrc;
			cdst++;
			csrc++;
		}
	}
	else
	{
		cdst = dst + n - 1;
		csrc = src + n - 1;
		while (n--)
			*cdst-- = *csrc--;
	}
	return (dst);
}
