/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:56:12 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 18:15:55 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (g_error_value = 256, 1);
	i = 0;
	while (((unsigned char *)s1)[i] && s1[i] == ((unsigned char *)s2)[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
