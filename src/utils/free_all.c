#include "../../include/minishell.h"

void	free_exec_struct(t_exec *exec)
{
	free_env(exec->env);
	free_env(exec->export);
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
