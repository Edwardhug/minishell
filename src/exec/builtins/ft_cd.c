#include "../../../include/minishell.h"

int	ft_cd(char **cmd, t_exec *exec)
{
	if (ft_strlen_doublechar(cmd) == 1)
	{
		chdir("/root");
		if (exec->nb_cmds > 1)
			exit(0);
		return (0);
	}
	if (chdir(cmd[1])) //chdir va tout simplement rediriger vers le chemin donné en argument.
	{
		perror("");
		g_error_value = -33;
	}
	if (exec->nb_cmds > 1)
		exit(0);
	return (0);
}
