#include "minishell.h"

int	ft_cd(char **cmd)
{
	chdir(cmd[1]); //chdir va tout simplement rediriger vers le chemin donné en argument.
	return (0);
}
/*
getcwd
chdir
faire gaffe à "cd -" et "cd ~" + "cd"
d'autres cas spéciaux mais osef
*/