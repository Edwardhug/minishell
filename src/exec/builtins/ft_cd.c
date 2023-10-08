#include "../../../include/minishell.h"

char	*get_var(t_exec *exec, char *var_name)
{
	t_env	*env;

	env = exec->env;
	while (env)
	{
		if (ft_strcmp(env->name, var_name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	change_oldpwd(t_exec *exec, char *actual_pwd)
{
	char	**arg;
	t_env    *args_tmp;

	arg = ft_calloc(2, sizeof(char *));
	if (!arg)
		return ;
	arg[0] = fill_oldpwd(actual_pwd);
	args_tmp = env_double_char_into_lst(arg);
	export_existing_value(args_tmp, exec);
}

void	go_to_old_pwd(char *oldpwd, t_exec *exec)
{
	char	*to_print;

	if (chdir(get_var(exec, "OLDPWD")))
	{
		perror("");
		g_error_value = -1;
		if (exec->nb_cmds > 1)
			exit(0);
		return ;
	}
	change_oldpwd(exec, oldpwd);
	to_print = getcwd(NULL, 0);
	ft_printf("%s\n", to_print);
	free(to_print);
	if (exec->nb_cmds > 1)
		exit(0);
	return ;
}

void	go_to_home(char *oldpwd, t_exec *exec)
{
	if (chdir(get_var(exec, "HOME")))
	{
		perror("");
		g_error_value = -1;
		if (exec->nb_cmds > 1)
			exit(0);
		return ;
	}
	change_oldpwd(exec, oldpwd);
	if (exec->nb_cmds > 1)
		exit(0);
	return ;
}

int	ft_cd(char **cmd, t_exec *exec)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);		// alloue avec malloc donc checker les leaks
	if (ft_strlen_doublechar(cmd) == 1 || ft_strcmp(cmd[1], "~") == 0)
	{
		change_oldpwd(exec, oldpwd);
		chdir("/root");
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
		return (go_to_old_pwd(oldpwd, exec), 0);
	else if (chdir(cmd[1])) //chdir va tout simplement rediriger vers le chemin donné en argument.
	{
		perror("");
		g_error_value = -1;
		if (exec->nb_cmds > 1)
			exit(0);
		return (0);
	}
	change_oldpwd(exec, oldpwd);
	// free(oldpwd);
	if (exec->nb_cmds > 1)
		exit(0);
	return (0);
}
