/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:28:48 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/14 13:01:45 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_new_line(char *str)
{
	int		i;
	char	*to_ret;
	int		j;

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
	j = 0;
	while (str[j] == ' ')
		j++;
	while (str[i + j] && str[i + j] != '\n')
	{
		to_ret[i] = str[i + j];
		i++;
	}
	to_ret[i] = 0;
	free(str);
	return (to_ret);
}

void	loop_main(char **path, int fd_standart, t_exec exec)
{
	char	*line;

	line = readline("Minishell> ");
	if (line == NULL)
		exit_and_write_it(path, fd_standart);
	add_history(line);
	line = remove_new_line(line);
	parsing_minishell(path, line, &exec);
	free(line);
	dup2(fd_standart, STDIN_FILENO);
	signal(SIGINT, sigint_handler);
}

void	loop_parsing(t_struct **list_word, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (i != 0 && ft_strcmp(get_last_node(*list_word)->str, "export") == 0)
			fill_var_node(list_word, find_end_var(line, &i, list_word));
		else if (i != 0
			&& ft_strcmp(get_last_node(*list_word)->str, "echo") == 0
			&& (line[i] == '\'' || line[i] == '\"'))
			fill_quote_node(list_word, find_last_quote(line, &i, list_word));
		else if (line[i] == '"' && (line[i + 1] == '<' || line[i + 1] == ')'))
			fill_quote_node(list_word, find_second_quote(line, &i));
		else if (line[i] == '"')
			fill_node(list_word, find_second_quote(line, &i));
		else
			fill_node(list_word, find_end_of_the_word(line, &i));
		if (line[i] == ' ')
			i++;
	}
}

int	main(int ac, char **av, char **env)
{
	char	**path;
	int		fd_standart;
	t_exec	exec;

	g_error_value = 0;
	exec.env = env_double_char_into_lst(env);
	exec.export = env_double_char_into_lst(env);
	fd_standart = dup(STDIN_FILENO);
	if (ac != 1)
		return (ft_printf("No arg needed\n"), 1);
	path = get_path(env);
	signals();
	while (1)
		loop_main(path, fd_standart, exec);
	rl_clear_history();
	free_tab(path);
	(void)av;
	return (0);
}
