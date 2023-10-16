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
	char	**arg_pwd;
	char	*tmp;
	t_env   *args_tmp;
	t_env   *args_tmp_pwd;

	arg = ft_calloc(2, sizeof(char *));
	if (!arg)
	{
		free(actual_pwd);
		free_exec_struct(exec);
		exit(EXIT_FAILURE);
	}
	arg_pwd = ft_calloc(2, sizeof(char *));
	if (!arg_pwd)
	{
		free(arg);
		free(actual_pwd);
		free_exec_struct(exec);
		exit(EXIT_FAILURE);
	}
	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		free_exec_struct(exec);
		free(arg);
		free(actual_pwd);
		exit(EXIT_FAILURE);
	}
	arg_pwd[0] = ft_strjoin("PWD=", tmp);
	free(tmp);
	arg[0] = fill_oldpwd(actual_pwd, exec);
	args_tmp = env_double_char_into_lst(arg);
	args_tmp_pwd = env_double_char_into_lst(arg_pwd);
	export_existing_value(args_tmp, exec, NULL);
	export_existing_value(args_tmp_pwd, exec, NULL);
	free_tab(arg_pwd);
	free_tab(arg);
}

void	go_to_old_pwd(char *oldpwd, t_exec *exec)
{
	char	*to_print;

	if (chdir(get_var(exec, "OLDPWD")))
	{
		perror("OLDPWD");
		g_error_value = -1;
		if (exec->nb_cmds > 1)
		{
			free(oldpwd);
			free_exec_struct(exec);
			exit(0);
		}
		return ;
	}
	change_oldpwd(exec, oldpwd);
	to_print = getcwd(NULL, 0);
	ft_printf("%s\n", to_print);
	free(to_print);
	if (exec->nb_cmds > 1)
	{
		free(oldpwd);
		free_exec_struct(exec);
		exit(0);
	}
	return ;
}

void	go_to_home(char *oldpwd, t_exec *exec)
{
	if (chdir(get_var(exec, "HOME")))
	{
		perror("HOME");
		g_error_value = -1;
		if (exec->nb_cmds > 1)
		{
			free(oldpwd);
			free_exec_struct(exec);
			exit(0);
		}
		return ;
	}
	change_oldpwd(exec, oldpwd);
	if (exec->nb_cmds > 1)
	{
		free_exec_struct(exec);
		free(oldpwd);
		exit(0);
	}
	return ;
}

int	ft_cd(char **cmd, t_exec *exec)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_putstr_fd("Can't go to this dir, moved to /lgabet\n", 2);
		chdir("/nfs/homes/lgabet");
		change_pwd(exec);
		return (0);
	}
	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
	{
		change_oldpwd(exec, oldpwd);
		chdir("/nfs/homes/lgabet");
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
		return (go_to_old_pwd(oldpwd, exec), 0);
	if (chdir(cmd[1]) == -1 || chdir(cmd[1]) == 0)
	{
		if (cmd[1][0] != '$' || cmd[2])
			g_error_value = -1;
		return (0);
	}
	change_oldpwd(exec, oldpwd);
	free(oldpwd); 
	if (exec->nb_cmds > 1)
	{
		free_exec_struct(exec);
		exit(0);
	}
	return (0);
}
