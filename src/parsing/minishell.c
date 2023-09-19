/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:28:48 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/19 17:14:50 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_new_line(char *str)
{
	int 	i;
	char	*to_ret;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	to_ret = malloc(sizeof(char) * (i + 1));
	if (!to_ret)
	{
		free(str);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		to_ret[i] = str[i];
		i++;
	}
	to_ret[i] = 0;
	free(str);
	return (to_ret);
}

int main(int ac, char **av, char **env)
{
	char	**path;
	char	*line;

	if (ac != 1)
		return (ft_printf("No arg needed\n"), 1);
	path = get_path(env);
	while (1)
	{
		signal_main_loop();
		line = readline("Minishell>");
		if (line == NULL)
			exit_and_write_it(path);
		add_history(line);
		line = remove_new_line(line);
		parsing_minishell(path, line, env);
		free(line);
	}
	(void)av;
	return (0);
}