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
		free_stuff_error(exec, "malloc", -1);
	}
	arg_pwd = ft_calloc(2, sizeof(char *));
	if (!arg_pwd)
	{
		free(arg);
		free(actual_pwd);
		free_stuff_error(exec, "malloc", -1);
	}
	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		free(arg);
		free(actual_pwd);
		free_stuff_error(exec, "malloc", -1);
	}
	arg_pwd[0] = ft_strjoin("PWD=", tmp);
	if (!arg_pwd[0])
	{
		free(tmp);
		free(arg);
		free(actual_pwd);
		free_stuff_error(exec, "malloc", -1);
	}
	free(tmp);
	arg[0] = fill_oldpwd(actual_pwd, exec);
	args_tmp = env_double_char_into_lst(arg, exec);
	free_tab(arg);
	args_tmp_pwd = env_double_char_into_lst(arg_pwd, exec);
	export_existing_value(args_tmp, exec, NULL);
	free_env(args_tmp);
	free_tab(arg_pwd);
	export_existing_value(args_tmp_pwd, exec, NULL);
	free_env(args_tmp_pwd);
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
	free(oldpwd);
	if (exec->nb_cmds > 1)
	{
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
	char	*home;
	int		result;

	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		return (g_error_value = -1, 0);
	}
	home = get_var_home(*exec);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_putstr_fd("Can't go to this dir, moved to home\n", 2);
		chdir(home);
		change_pwd(exec);
		g_error_value = -1;
		return (0);
	}
	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
	{
		chdir(home);
		change_oldpwd(exec, oldpwd);
		return (0);
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
		return (go_to_old_pwd(oldpwd, exec), 0);
	result = chdir(cmd[1]);
	if (result == 0)
	{
		free(oldpwd);
		return (0);
	}
	if (result == -1)
		ft_putstr_fd(" no such file or directory\n", 2);
	if (cmd[1][0] != '$' || cmd[2])
		g_error_value = -1;
	change_oldpwd(exec, oldpwd);
	free(oldpwd); 
	if (exec->nb_cmds > 1)
	{
		free_exec_struct(exec);
		exit(0);
	}
	return (0);
}
