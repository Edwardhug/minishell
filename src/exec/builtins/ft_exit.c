/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 09:01:27 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/21 11:50:35 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static	void	portable_free_exec(t_exec *exec)
{
	free_env(exec->env);
	free_env(exec->export);
	close(exec->fd_stand);
	if (exec->line)
		free(exec->line);
	if (exec->list_word)
		free_list(&exec->list_word);
	if (exec->pid_tab)
		free(exec->pid_tab);
}

static int	is_not_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if ((arg[i] < '0' || arg[i] > '9') && (arg[i] != '+' && arg[i] != '-'))
			return (1);
		i++;
	}
	return (0);
}

static int	exit_not_number(char **cmd, t_exec *exec, int are_pipes)
{
	ft_error_message_arg(cmd[0], cmd[1],
		": numeric argument required\n");
	shlvl(exec, 0, 0);
	if (are_pipes)
		portable_free_exec(exec);
	else
		free_exec_struct(exec);
	free_tab(cmd);
	exit(2);
}

static int	if_one_command(char **cmd, t_exec *exec,
	int are_pipes, int overflow)
{
	long long	status;

	status = 0;
	if (cmd[2])
	{
		ft_error_message(cmd[0], ": too many arguments\n");
		if (exec->nb_cmds > 1)
		{
			free_exec_fork(exec);
			exit(1);
		}
		g_error_value = -1;
		return (1);
	}
	status = ft_atoi_ll(cmd[1], &overflow) % 256;
	if (is_not_number(cmd[1]) == 1 || overflow == 1)
		exit_not_number(cmd, exec, are_pipes);
	if (are_pipes)
		portable_free_exec(exec);
	else
		free_exec_struct(exec);
	free_tab(cmd);
	exit(status);
	return (0);
}

int	ft_exit(char **cmd, t_exec *exec, int are_pipes)
{
	if (!are_pipes)
		ft_putstr_fd("exit\n", 1);
	if (cmd[1])
		if (if_one_command(cmd, exec, are_pipes, 0) == 1)
			return (1);
	shlvl(exec, 0, 0);
	if (are_pipes)
		portable_free_exec(exec);
	else
		free_exec_struct(exec);
	free_tab(cmd);
	close(exec->fd_stand);
	exit(g_error_value / 256);
	return (0);
}
