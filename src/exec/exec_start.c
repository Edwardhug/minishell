/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:08:24 by lezard            #+#    #+#             */
/*   Updated: 2023/10/21 00:12:14 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	have_pipe(t_struct *temp_list)
{
	while (temp_list->next && temp_list->type != PIPE)
		temp_list = temp_list->next;
	if (temp_list->type == PIPE)
		return (1);
	return (0);
}

int	number_of_cmd(t_struct *list_word)
{
	int	i;

	i = 1;
	while (list_word->next)
	{
		if (list_word->type == PIPE)
			i++;
		list_word = list_word->next;
	}
	return (i);
}

void	wait_all_process(int *pid, t_struct *list_word, t_exec *exec)
{
	int		cmd_to_finish;
	int		i;
	sig_t	old_signal[2];
	int		status;

	cmd_to_finish = number_of_cmd(list_word);
	i = 0;
	old_signal[0] = signal(SIGINT, sigint_handler_in_process);
	old_signal[1] = signal(SIGQUIT, sigquit_handler_in_process);
	while (i < cmd_to_finish)
	{
		waitpid(pid[i], &status, WUNTRACED);
		i++;
	}
	free(pid);
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	change_value_builtin(list_word, exec, &status);
	g_error_value = status;
}

void	begin_execution(t_exec *exec, t_struct *list_word, int i)
{
	t_struct	*temp_list;

	change_underscore(list_word->str, exec);
	exec->nb_cmds = number_of_cmd(list_word);
	exec->pid_tab = malloc(sizeof(int) * exec->nb_cmds);
	if (!exec->pid_tab)
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	temp_list = list_word;
	exec->list_word = list_word;
	while (temp_list)
	{
		exec->pid_tab[i] = t_exec_cmd(temp_list, exec);
		if (ft_strcmp(list_word->str, "$?") == 0)
		{
			wait(0);
			free(exec->pid_tab);
			g_error_value = 127 * 256;
			return ;
		}
		if (to_next_cmd(&temp_list))
			break ;
		i++;
	}
	wait_all_process(exec->pid_tab, list_word, exec);
}
