#include "minishell.h"

int	ft_exit(char **cmd)
{
	int	status;

	status = 0;
	if (cmd[1])
	{
		if (cmd[2]) //si il y a plus d'un argument c'est une erreur
			return (perror("exit: too many arguments"), 1);
		status = ft_atoi(cmd[1]);
	}
	//free and close everything
	exit(status);
	return (0);
}