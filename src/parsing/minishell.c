/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lgabet <lgabet@student.42lyon.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/06/14 14:28:48 by lgabet			#+#	#+#			 */
/*   Updated: 2023/10/18 12:47:08 by lgabet		   ###   ########.fr	   */
/*																			*/
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

void	loop_main(t_exec *exec)
{
	char	*line;

	exec->fd_stand = dup(STDIN_FILENO);
	line = readline("Minishell> ");
	if (line == NULL)
		exit_and_write_it(exec);
	if (line[0])
		add_history(line);
	line = remove_new_line(line);
	exec->line = line;
	parsing_minishell(line, exec);
	free(line);
	dup2(exec->fd_stand, STDIN_FILENO);
	close(exec->fd_stand);
	signal(SIGINT, sigint_handler);
}

void	loop_parsing(t_struct **list_word, char *line, t_exec *exec)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (i != 0 && ft_strcmp(get_last_node(*list_word)->str, "export") == 0)
			fill_var_node(list_word, find_end_var(line, &i, list_word, exec),
				exec);
		else if (i != 0
			&& ft_strcmp(get_last_node(*list_word)->str, "echo") == 0
			&& (line[i] == '\'' || line[i] == '\"'))
			fill_quote_node(list_word,
				find_last_quote(line, &i, list_word, exec), exec);
		else if (line[i] == '"' && (line[i + 1] == '<' || line[i + 1] == ')'))
			fill_quote_node(list_word, find_second_quote(line, &i, exec), exec);
		else if (line[i] == '"')
			fill_node(list_word, find_second_quote(line, &i, exec), exec);
		else
			fill_node(list_word, find_end_of_the_word(line, &i), exec);
		if (line[i] == ' ')
			i++;
	}
}

static void	if_env_i(t_exec *exec)
{
	char	*cwd;
	char	*pwd;

	cwd = malloc(sizeof(char *) * (PATH_MAX + 1));
	if (!cwd)
	{
		ft_putstr_fd("malloc error\n", 2);
		exit(EXIT_FAILURE);
	}
	shlvl(exec, 1, 1);
	exec->env->next = ft_lstnew_env("_=", 1);
	exec->export->next = ft_lstnew_env("_=", 1);
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		pwd = ft_strjoin("PWD=", cwd);
		if (!pwd)
		{
			ft_putstr_fd("malloc error\n", 2);
			free(cwd);
			exit(EXIT_FAILURE);
		}
		exec->env->next->next = ft_lstnew_env(pwd, 3);
		exec->export->next->next = ft_lstnew_env(pwd, 3);
		free(pwd);
	}
	free(cwd);
}

int	main(int ac, char **av, char **env)
{
	t_exec	exec;

	if (ac != 1)
		return (ft_printf("No arg needed\n"), 1);
	exec.list_word = NULL;
	if (!env[0])
		if_env_i(&exec);
	else
	{
		exec.env = NULL;
		exec.export = NULL;
		exec.pid_tab = NULL;
		exec.clean_cmd = NULL;
		exec.env = env_double_char_into_lst(env, &exec);
		exec.export = env_double_char_into_lst(env, &exec);
	}
	signals();
	while (1)
		loop_main(&exec);
	rl_clear_history();
	(void)av;
	return (0);
}
