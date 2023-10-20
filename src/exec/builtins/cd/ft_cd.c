/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:09:36 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 11:31:27 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	change_oldpwd(t_exec *exec, char *actual_pwd)
{
	malloc_oldpwd_var(exec, actual_pwd);
	exec->arg_pwd[0] = ft_strjoin("PWD=", exec->tmp);
	if (!exec->arg_pwd[0])
	{
		free(exec->tmp);
		free(exec->arg);
		free(actual_pwd);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
	free(exec->tmp);
	exec->arg[0] = fill_oldpwd(actual_pwd, exec);
	exec->args_tmp = env_double_char_into_lst(exec->arg, exec);
	free_tab(exec->arg);
	exec->args_tmp_pwd = env_double_char_into_lst(exec->arg_pwd, exec);
	export_existing_value(exec->args_tmp, exec, NULL);
	free_env(exec->args_tmp);
	free_tab(exec->arg_pwd);
	export_existing_value(exec->args_tmp_pwd, exec, NULL);
	free_env(exec->args_tmp_pwd);
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
		free_exec_fork(exec);
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
			free_exec_fork(exec);
			exit(0);
		}
		return ;
	}
	change_oldpwd(exec, oldpwd);
	if (exec->nb_cmds > 1)
	{
		free_exec_fork(exec);
		free(oldpwd);
		exit(0);
	}
	return ;
}

static int	interprete_result(t_exec *exec, char *oldpwd, int result)
{
	if (result == 0)
	{
		change_oldpwd(exec, oldpwd);
		free(oldpwd);
		if (exec->nb_cmds > 1)
		{
			free_exec_fork(exec);
			exit(0);
		}
		return (0);
	}
	if (result == -1)
	{
		ft_putstr_fd(" no such file or directory\n", 2);
		free(oldpwd);
		if (exec->nb_cmds > 1)
		{
			free_exec_fork(exec);
			exit(1);
		}
		g_error_value = -1;
		return (0);
	}
	return (0);
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
		no_oldpwd(exec, home);
	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
	{
		chdir(home);
		change_oldpwd(exec, oldpwd);
		free(oldpwd);
		return (0);
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
		return (go_to_old_pwd(oldpwd, exec), 0);
	result = chdir(cmd[1]);
	interprete_result(exec, oldpwd, result);
	return (0);
}
