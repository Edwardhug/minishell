/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:28:48 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/26 18:54:26 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_new_line(char *str)
{
	int		i;
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
	int		fd_standart;

	fd_standart = dup(STDIN_FILENO);
	if (ac != 1)
		return (ft_printf("No arg needed\n"), 1);
	path = get_path(env);
	signals();
	while (1)
	{
		line = readline("Minishell> ");
		if (line == NULL)
			exit_and_write_it(path, fd_standart);
		add_history(line);
		line = remove_new_line(line);
		parsing_minishell(path, line, env);
		free(line);
		dup2(fd_standart, STDIN_FILENO);
		signal(SIGINT, sigint_handler);
	}
	// rl_clear_history();
	free_tab(path);
	(void)av;
	return (0);
}