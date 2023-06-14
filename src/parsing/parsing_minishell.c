/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:50:18 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/14 16:32:33 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing_minishell(char **path, char *line, char **env)
{
	// char		**splited_line;
	// t_struct	to_send;

	if (line[0] == '\n')
		return ;
	ft_printf("%s", line);
	// splited_line = ft_split(line, ' ');
	// if (splited[0][0] == '<' && splited[0][1] != '<')
	// 	to_send.stdin = open(splited[1], O_RDONLY);
	(void)path;
	(void)env;
}