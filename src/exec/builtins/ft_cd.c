#include "../../../include/minishell.h"

char	*get_pwd(t_exec *exec)
{
	t_env	*tmp;

	tmp = exec->env;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_old_pwd(t_exec *exec, char *pwd)
{
	t_env	*tmp;

	tmp = exec->env;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
			ft_printf("new OLDPWD = %s\n", tmp->value);
			return ;
		}
		tmp = tmp->next;
	}
}

void	change_pwd(t_exec *exec)
{
	t_env	*tmp;
	char	cwd[1024];

	tmp = exec->env;
	getcwd(cwd, sizeof(cwd));
	while (tmp->next)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(cwd);
			ft_printf("new PWD = %s\n", tmp->value);
			return ;
		}
		tmp = tmp->next;
	}
}

int	ft_cd(char **cmd, t_exec *exec)
{
	// char	*pwd; 

	// pwd = get_pwd(exec);
	if (ft_strlen_doublechar(cmd) == 1)
		chdir("/root");
	else if (chdir(cmd[1])) //chdir va tout simplement rediriger vers le chemin donné en argument.
	{
		perror("");
		g_error_value = -1;
		if (exec->nb_cmds > 1)
			exit(0);
		return (0);
	}
	// ft_printf("OLDPWD = %s\n", pwd);
	// change_old_pwd(exec, pwd);			// need export
	// change_pwd(exec);					// need export
	if (exec->nb_cmds > 1)
		exit(0);
	return (0);
}
