/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:28:48 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/14 16:06:10 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int main(int ac, char **av, char **env)
{
	char	**path;
	char	*line;

	if (ac != 1)
		return (ft_printf("No arg needed\n"), 1);
	path = get_path(env);
	while (1)
	{
		ft_printf("minishell>");
		line = get_next_line(0);
		if (line == NULL)
			break ;
		parsing_minishell(path, line, env);
		free(line);
	}
	free_tab(path);
	(void)av;
	return (0);
}