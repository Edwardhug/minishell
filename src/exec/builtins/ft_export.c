#include "../../../include/minishell.h"

int	ft_export(t_exec *exec)
{
	if (exec->nb_cmds > 1)
		exit(0);
	return (0);
}