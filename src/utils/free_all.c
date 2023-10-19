#include "../../include/minishell.h"

void	free_exec_struct(t_exec *exec)
{
	free_env(exec->env);
	close(exec->fd_stand);
	free_env(exec->export);
	rl_clear_history();
	free(exec->line);
	if (exec->pid_tab)
		free(exec->pid_tab);
	if (exec->clean_cmd)
		free_tab(exec->clean_cmd);
	if (exec->list_word)
		free_list(&exec->list_word);
}

void	free_stuff_error(t_exec *exec, char *strperror, int error_value)
{
	perror(strperror);
	free_exec_struct(exec);
	if (error_value >= 0)
		exit(error_value);
	else
		exit(EXIT_FAILURE);
}

void	change_name(t_env **new, char *str, int *i, int nb)
{
	if (str[0] == '=')
	{
		while (str[*i] == '=')
		{
			(*new)->name[*i] = '=';
			(*i)++;
		}
		(*new)->name[*i] = '\0';
	}
	else
	{
		ft_strncpy((*new)->name, str, nb);
		(*new)->name[nb] = '\0';
	}
}
