/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:28:48 by lgabet            #+#    #+#             */
/*   Updated: 2023/10/09 19:26:04 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_error_value = 0;

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

static void if_env_i(t_exec *exec)
{
	(void)exec;
	//prendre pwd
	//prendre last command avec path _ (le créer sans l'initialiser en vrai)
	//prendre old_pwd
	//créer shlvl
	return ;
}

int	main(int ac, char **av, char **env)
{
	char	**path;
	char	*line;
	int		fd_standart;
	t_exec	exec;

	if (!env)
		if_env_i(&exec);
	else
	{
		exec.env = env_double_char_into_lst(env);
		exec.export = env_double_char_into_lst(env);
	}
//	exec.export = ft_lstcpy(exec.env);
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
		parsing_minishell(path, line, &exec);
		free(line);
		dup2(fd_standart, STDIN_FILENO);
		signal(SIGINT, sigint_handler);
	}
	// rl_clear_history();
	free_tab(path);
	(void)av;
	return (0);
}