/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:50:55 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/20 19:50:56 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_pipe(t_struct **list_word)
{
	char	*pipe;

	if (((*list_word)->next && get_last_node(*list_word)->str[0] == '$')
		&& get_last_node(*list_word)->type == CMD)
	{
		pipe = ft_calloc(2, sizeof(char));
		if (!pipe)
			return ;
		pipe[0] = '|';
		add_node_back(list_word, new_node(pipe, PIPE));
	}
}
