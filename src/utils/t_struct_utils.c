/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_struct_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:20:41 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/18 13:22:30 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t t_struct_strlen(t_struct *list_word)
{
	size_t i;

	i = 0;
	while (list_word)
		i++;
	return (i);
}