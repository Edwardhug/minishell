#include "../../../include/minishell.h"

static int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if ((arg[i] < '0' || arg[i] > '9') && (arg[i] != '+' && arg[i] != '-'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(char **cmd, t_exec *exec)
{
	long long	status;

	status = 0;
	(void)exec;
	if (cmd[1])
	{
		if (cmd[2]) //si il y a plus d'un argument c'est une erreur
		{
			ft_putstr_fd(" too many arguments\n", 2);
			g_error_value = -1; // le message à renvoyer est 1
			return (1);
		}
		if (is_number(cmd[1]) == 1)
		{
			ft_putstr_fd(" numeric argument required\n", 2);
			exit(2);
		}
		status = ft_atoi(cmd[1]) % 256;
		exit(status);
	}
	//free and close everything
	// exit(status);
	exit(0);
	return (0);
}