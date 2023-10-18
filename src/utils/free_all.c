#include "../../include/minishell.h"

void	free_exec_struct(t_exec *exec)
{
	free_env(exec->env);
	free_env(exec->export);
	if (exec->list_word)
		free_list(&exec->list_word);
}

void	free_stuff_error(t_exec *exec, int which, int error_value)
{
	if (which == 0)
		perror("malloc");
	if (which == 1)
		perror("access");
	if (which == 2)
		perror("execve");
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
