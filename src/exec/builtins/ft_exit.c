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
	ft_putstr_fd("exit\n", 1);
	if (cmd[1])
	{
		if (cmd[2])
		{
			ft_error_message(cmd[0], ": too many arguments\n");
			g_error_value = -1;
			return (1);
		}
		if (is_number(cmd[1]) == 1)
		{
			ft_error_message_arg(cmd[0], cmd[1], ": numeric argument required\n");
			shlvl(exec, 0, 0);
			free_exec_struct(exec);
			exit(2);
		}
		status = ft_atoi(cmd[1]) % 256;
		free_exec_struct(exec);
		exit(status);
	}
	shlvl(exec, 0, 0);
	free_tab(cmd);
	free(exec->pid_tab);
	free_exec_struct(exec);
	close(exec->fd_stand);
	exit(g_error_value / 256);
	return (0);
}