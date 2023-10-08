#include "../../../include/minishell.h"

void	put_old_pwd_in_char(char **arg)
{
	(*arg)[0] = 'O';
	(*arg)[1] = 'L';
	(*arg)[2] = 'D';
	(*arg)[3] = 'P';
	(*arg)[4] = 'W';
	(*arg)[5] = 'D';
	(*arg)[6] = '=';
}

void	put_pwd_in_char(char **arg)
{
	(*arg)[1] = 'P';
	(*arg)[2] = 'W';
	(*arg)[3] = 'D';
	(*arg)[4] = '=';
}

char	*fill_oldpwd(char *actual_pwd)
{
	int		i;
	int		size;
	char	*arg;

	size = ft_strlen("OLDPWD=") + ft_strlen(actual_pwd) + 1;
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
			put_old_pwd_in_char(&arg);
			i = 7;
		}
		arg[i] = actual_pwd[i - 7];
		i++;
	}
	return(arg);
}

char	*fill_newpwd(char *actual_pwd)
{
	int		i;
	int		size;
	char	*arg;

	size = ft_strlen("PWD=") + ft_strlen(actual_pwd) + 1;
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
			i = 4;
		}
		arg[i] = actual_pwd[i - 4];
		i++;
	}
	return(arg);
}

void	change_pwd(t_exec *exec)
{
	char	*newpwd;
	char	**arg;
	t_env    *args_tmp;

	newpwd = getcwd(NULL, 0);		//faut peut etre free
	arg = ft_calloc(2, sizeof(char *));
	if (!arg)
		return ;
	arg[0] = fill_newpwd(newpwd);
	args_tmp = env_double_char_into_lst(arg);
	export_existing_value(args_tmp, exec);
}