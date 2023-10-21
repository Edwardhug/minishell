/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_oldpwd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:28:19 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/21 11:03:01 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	malloc_oldpwd_var(t_exec *exec, char *actual_pwd)
{
	exec->arg = ft_calloc(2, sizeof(char *));
	if (!exec->arg)
	{
		free(actual_pwd);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
	exec->arg_pwd = ft_calloc(2, sizeof(char *));
	if (!exec->arg_pwd)
	{
		free(exec->arg);
		free(actual_pwd);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
	exec->tmp = getcwd(NULL, 0);
	if (!exec->tmp)
	{
		free(exec->arg);
		free(actual_pwd);
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	}
}

int	no_oldpwd(t_exec *exec, char *home, char **cmd)
{
	ft_putstr_fd("can't go to this dir, moved to home\n", 2);
	if (home)
		chdir(home);
	else
	{
		free_tab(cmd);
		free_stuff_error(exec, NULL, "didn't found home\nexit\n", -1);
	}
	change_pwd(exec);
	g_error_value = -1;
	return (0);
}

void	no_actual_pwd(t_exec *exec, char **cmd)
{
	free_tab(exec->arg);
	free_tab(exec->arg_pwd);
	free_tab(cmd);
	free_stuff_error(exec, NULL, "no pwd\nexit\n", -1);
}

void	cd_tilde(char *home, char *oldpwd, char **cmd, t_exec *exec)
{
	chdir(home);
	change_oldpwd(exec, oldpwd, cmd);
	free(oldpwd);
}

void	exit_if_fork(t_exec *exec)
{
	if (exec->nb_cmds > 1)
	{
		free_exec_fork(exec);
		exit(0);
	}
}
