#include "../../../include/minishell.h"

int	ft_cd(char **cmd)
{
	chdir(cmd[1]);
	return (0);
}
/*
getcwd
chdir
faire gaffe à "cd -" et "cd ~" + "cd"
d'autres cas spéciaux mais osef
*/