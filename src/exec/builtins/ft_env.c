#include "minishell.h"

int	ft_env(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->char_env[i])
	{
		ft_printf("%s\n", exec->char_env[i]);
		i++;
	}
	if (exec->nb_cmds > 1)
		exit(0);
	return (0);
}