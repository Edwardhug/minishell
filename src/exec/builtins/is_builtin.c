#include "../../../include/minishell.h"

int	is_builtin_alone(char **cmd, t_exec *exec)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(cmd, exec), 1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd(exec), 1);
	// else if (ft_strcmp(cmd[0], "echo") == 0)
	// 	return (ft_echo(cmd, exec), 1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd, exec), 1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(cmd, exec), 1);
	// else if (ft_strcmp(cmd[0], "unset") == 0)
	// 	return (ft_unset(cmd, exec), 1);
	// else if (ft_strcmp(cmd[0], "env") == 0)
	// 	return (ft_env(exec), 1); 
	return (0);
}

int	is_builtin_fork(char **cmd, t_exec *exec)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(cmd, exec), 1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd(exec), 1);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd, exec), 1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd, exec), 1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(cmd, exec), 1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(cmd, exec), 1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env(exec), 1);
	return (0);
}
