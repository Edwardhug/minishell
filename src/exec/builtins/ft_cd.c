#include "../../../include/minishell.h"

int	ft_cd(char **cmd, t_exec *exec)
{
	if (ft_strlen_doublechar(cmd) == 1)
		chdir("/root");
	chdir(cmd[1]); //chdir va tout simplement rediriger vers le chemin donné en argument.
	if (exec->nb_cmds > 1)
		exit(0);
	g_error_value = 0;
	return (0);
}
/*
getcwd
chdir
faire gaffe à "cd -" et "cd ~" + "cd"
d'autres cas spéciaux mais osef
*/