#include "../../../include/minishell.h"

int	ft_exit(char **cmd, t_exec *exec)
{
	// int	status;

	// status = 0;
	(void)exec;
	if (cmd[1])
	{
		if (cmd[2]) //si il y a plus d'un argument c'est une erreur
		{
			perror("exit: too many arguments");
			exit(1);
		}
			return (perror("exit: too many arguments"), 1);
		// status = ft_atoi(cmd[1]);
	}
	//free and close everything
	// exit(status);
	exit(0);
	return (0);
}