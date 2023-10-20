/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:58:52 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 21:59:05 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_exec_fork(t_exec *exec)
{
	free_env(exec->env);
	free_env(exec->export);
	close(exec->fd_stand);
	if (exec->line)
		free(exec->line);
	if (exec->clean_cmd)
		free_tab(exec->clean_cmd);
	if (exec->list_word)
		free_list(&exec->list_word);
	if (exec->pid_tab)
		free(exec->pid_tab);
}

void	free_exec_struct(t_exec *exec)
{
	(void)exec;
	free_exec_fork(exec);
	rl_clear_history();
}

void	free_stuff_error(t_exec *exec, char *name,
	char *strperror, int error_value)
{
	if (name)
		ft_putstr_fd(name, 2);
	ft_putstr_fd(strperror, 2);
	free_exec_struct(exec);
	if (error_value >= 0)
		exit(error_value);
	else
		exit(EXIT_FAILURE);
}

void	change_name(t_env **new, char *str, int *i, int nb)
{
	if (str[0] == '=')
	{
		while (str[*i] == '=')
		{
			(*new)->name[*i] = '=';
			(*i)++;
		}
		(*new)->name[*i] = '\0';
	}
	else
	{
		ft_strncpy((*new)->name, str, nb);
		(*new)->name[nb] = '\0';
	}
}
