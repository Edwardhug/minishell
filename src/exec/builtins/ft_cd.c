#include "../../../include/minishell.h"

char	*get_pwd(t_exec *exec)
{
	t_env	*env;

	env = exec->lst_env;
	while (env->next)
	{
		if (ft_strcmp(env->name, "PWD") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	change_old_pwd(t_exec *exec, char *pwd)
{
	t_env	*env;

	env = exec->lst_env;
	while (env->next)
	{
		if (ft_strcmp(env->name, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(pwd);
			ft_printf("new OLDPWD = %s\n", env->value);
			return ;
		}
		env = env->next;
	}
}

void	change_pwd(t_exec *exec)
{
	t_env	*env;
	char	cwd[1024];

	env = exec->lst_env;
	getcwd(cwd, sizeof(cwd));
	while (env->next)
	{
		if (ft_strcmp(env->name, "PWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(cwd);
			ft_printf("new PWD = %s\n", env->value);
			return ;
		}
		env = env->next;
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
		if (exec->nb_cmds > 1)
			exit(0);
		g_error_value = -33;
		return (0);
	}
	// ft_printf("OLDPWD = %s\n", pwd);
	// change_old_pwd(exec, pwd);			// need export
	// change_pwd(exec);					// need export
	if (exec->nb_cmds > 1)
		exit(0);
	return (0);
}
