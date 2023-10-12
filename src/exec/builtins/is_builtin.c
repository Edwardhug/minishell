#include "../../../include/minishell.h"

void	show_env_var2(t_exec *exec, char *arg)
{
	t_env	*tmp;

	tmp = exec->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, arg + 1, ft_strlen(tmp->name)) == 0)
		{
			ft_printf("%s", tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

int	is_env_var2(t_exec *exec, char *arg)
{
	t_env	*tmp;
	int		i;

	tmp = exec->env;
	i = 1;
	if (arg[0] == '\'' && arg[1] == '$')
	{
		while (arg[i] && arg[i] != '\'')
		{
			ft_printf("%c", arg[i]);
			i++;
		}
		return (1);
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->name, arg + 1, ft_strlen(tmp->name)) == 0)
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	special_builtin(char **cmd, t_exec *exec)
{
	if (is_env_var2(exec, cmd[0]))
	{
		show_env_var2(exec, cmd[0]);
		ft_putstr_fd(" : Is a directory\n", 2);
		exit(126);
	}
	if (!cmd[0][1])
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	if (cmd[0][1] == '?')
	{
		print_return_value();
		exit(127);
	}
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

int	is_builtin_alone(char **cmd, t_exec *exec)
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
	else if (ft_strncmp(cmd[0], "$", 1) == 0)
		return (special_builtin(cmd, exec), 1);
	return (0);
}
