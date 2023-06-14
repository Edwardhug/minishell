/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:17:17 by lgabet            #+#    #+#             */
/*   Updated: 2023/03/30 11:56:36 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		i;

	while (n > 0)
	{
		i = *(unsigned char *)s1++ - *(unsigned char *)s2++;
		if (i != 0)
			return (i);
		n--;
	}
	return (0);
}
