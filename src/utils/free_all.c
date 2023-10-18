#include "../../include/minishell.h"

void	free_exec_struct(t_exec *exec)
{
	close(exec->fd_stand);
	free_env(exec->env);
	free_env(exec->export);
	if (exec->list_word)
		free_list(&exec->list_word);
}

void	free_stuff_error(t_exec *exec)
{
	perror("malloc");
	free_exec_struct(exec);
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
