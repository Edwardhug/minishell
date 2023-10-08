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

// void	change_old_pwd(t_exec *exec, char *pwd)
// {
// 	t_env	*tmp;

// 	tmp = exec->env;
// 	while (tmp->next)
// 	{
// 		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
// 		{
// 			free(tmp->value);
// 			tmp->value = ft_strdup(pwd);
// 			ft_printf("new OLDPWD = %s\n", tmp->value);
// 			return ;
// 		}
// 		tmp = tmp->next;
// 	}
// }

void	put_pwd_in_char(char **arg)
{
	(*arg)[0] = 'P';
	(*arg)[1] = 'W';
	(*arg)[2] = 'D';
	(*arg)[3] = '=';
	(*arg)[4] = '\"';
}

char	*fill_pwd(char *actual_pwd)
{
	int		i;
	int		size;
	char	*arg;

	size = ft_strlen("PWD=\"") + ft_strlen(actual_pwd) + 2;
	i = 0;
	arg = ft_calloc(size, sizeof(char));
	if (!arg)
	{
		free(arg);
		return (NULL);
	}
	while (i < size - 1)
	{
		if (i == 0)
		{
			put_pwd_in_char(&arg);
			i = 5;
		}
		arg[i] = actual_pwd[i - 5];
		i++;
	}
	arg[i - 1] = '\"';
	return(arg);
}

void	change_pwd(t_exec *exec, char *actual_pwd)
{
	char	**arg;
	t_env    *args_tmp;

	arg = ft_calloc(2, sizeof(char *));
	if (!arg)
		return ;
	arg[0] = fill_pwd(actual_pwd);
	// ft_printf("%s\n", arg[0]);
	args_tmp = env_double_char_into_lst(arg);
	export_existing_value(args_tmp, exec);
}

int	ft_cd(char **cmd, t_exec *exec)
{
	char	*pwd;

	pwd = get_pwd(exec);
	ft_printf("PWD before = %s\n", pwd);
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
	change_pwd(exec, pwd);
	pwd = get_pwd(exec);
	ft_printf("PWD after = %s\n", pwd);
	if (exec->nb_cmds > 1)
		exit(0);
	return (0);
}
