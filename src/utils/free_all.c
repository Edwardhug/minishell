#include "../../include/minishell.h"

void	free_exec_struct(t_exec *exec)
{
	free_env(exec->env);
	free_env(exec->export);
}