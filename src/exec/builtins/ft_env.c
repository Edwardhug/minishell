#include "../../../include/minishell.h"

int	ft_env(t_exec *exec)
{
	int		i;
	char	**char_env;

	char_env = env_lst_into_double_char(exec->env);
	i = 0;
	while (char_env[i])
	{
		ft_printf("%s\n", char_env[i]);
		i++;
	}
	if (exec->nb_cmds > 1)
		exit(0);
	return (0);
}