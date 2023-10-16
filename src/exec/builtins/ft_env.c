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
	free_tab(char_env);
	if (exec->nb_cmds > 1)
	{
		free_exec_struct(exec);
		exit(0);
	}
	return (0);
}