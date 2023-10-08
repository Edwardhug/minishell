#include "../../../include/minishell.h"

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
	change_pwd(exec);
}

int	ft_cd(char **cmd, t_exec *exec)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);		// alloue avec malloc donc checker les leaks
	if (ft_strlen_doublechar(cmd) == 1)
	{
		change_oldpwd(exec, oldpwd);
		chdir("/root");
	}
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
