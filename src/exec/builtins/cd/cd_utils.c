/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:09:12 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/21 03:16:17 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

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

char	*fill_oldpwd(char *actual_pwd, t_exec *exec)
{
	int		i;
	int		size;
	char	*arg;

	if (!actual_pwd)
		free_stuff_error(exec, "NULL", "pwd empty\nexit\n", -1);
	size = ft_strlen("OLDPWD=") + ft_strlen(actual_pwd) + 1;
	i = 0;
	arg = ft_calloc(size, sizeof(char));
	if (!arg)
		free_arg_oldpwd(arg, actual_pwd, exec);
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
	return (arg);
}

void	change_pwd(t_exec *exec)
{
	char	**arg_pwd;
	char	*join_arg_pwd;
	t_env	*args_tmp_pwd;

	arg_pwd = ft_calloc(2, sizeof(char *));
	if (!arg_pwd)
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	join_arg_pwd = getcwd(NULL, 0);
	arg_pwd[0] = ft_strjoin("PWD=", join_arg_pwd);
	free(join_arg_pwd);
	args_tmp_pwd = env_double_char_into_lst(arg_pwd, exec);
	export_existing_value(args_tmp_pwd, exec, NULL, 0);
	free_tab(arg_pwd);
	free_env(args_tmp_pwd);
}

char	*get_var_home(t_exec exec)
{
	while (exec.env)
	{
		if (ft_strcmp(exec.env->name, "HOME") == 0)
			return (exec.env->value);
		exec.env = exec.env->next;
	}
	return (NULL);
}
