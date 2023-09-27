#include "minishell.h"

int	is_builtin(char	**cmd)
{
	if (ft_strnstr(cmd[0], "cd", 2) != NULL)
		return (ft_cd(cmd), 1);
	else if (ft_strnstr(cmd[0], "pwd", 3) != NULL)
		return (ft_pwd(), 1);
	else if (ft_strnstr(cmd[0], "echo", 4) != NULL)
		return (ft_echo(cmd), 1);
	else if (ft_strnstr(cmd[0], "exit", 4) != NULL)
		return (ft_exit(cmd), 1);
	return (0);
}

int	have_pipe(t_struct *temp_list)
{
	while (temp_list->next && temp_list->type != PIPE)
		temp_list = temp_list->next;
	if (temp_list->type == PIPE)
		return (1);
	return (0);
}

int	number_of_cmd(t_struct *list_word)
{
	int	i;

	i = 1;
	while (list_word->next)
	{
		if (list_word->type == PIPE)
			i++;
		list_word = list_word->next;
	}
	return (i);
}

void	wait_all_process(int *pid, t_struct *list_word)
{
	int	cmd_to_finish;
	int	i;

	cmd_to_finish = number_of_cmd(list_word);
	i = 0;
	while (i <= cmd_to_finish)
	{
		waitpid(pid[i], NULL, WUNTRACED);
		i++;
	}
}

void	begin_execution(char **path, t_env *env, t_struct *list_word)
{
	int			pid_tab[number_of_cmd(list_word)];
	int			i;
	t_struct	*temp_list;

		i = 0;
		(void)path;
		temp_list = list_word;
		while (temp_list)
		{
			change_stdin(list_word, temp_list);
			pid_tab[i] = t_exec_cmd(temp_list, env);
			while (temp_list->next && temp_list->type != PIPE)
			{
				temp_list = temp_list->next;
			}
			if (temp_list->type == PIPE)
				temp_list = temp_list->next;
			else
				break ;
			i++;
		}
		wait_all_process(pid_tab, list_word);
}
