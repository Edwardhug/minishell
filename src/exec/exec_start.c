/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:08:24 by lezard            #+#    #+#             */
/*   Updated: 2023/10/14 14:08:38 by lgabet           ###   ########.fr       */
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
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	change_value_builtin(list_word, exec, &status);
	g_error_value = status;
}

void	begin_execution(char **path, t_exec *exec, t_struct *list_word)
{
	int			*pid_tab;
	int			i;
	t_struct	*temp_list;
	t_fd		fd;

	(void)path;
	fd.fd_in = 0;
	fd.fd_out = 1;
	change_underscore(list_word->str, exec);
	exec->nb_cmds = number_of_cmd(list_word);
	pid_tab = malloc(sizeof(int) * exec->nb_cmds);
	if (!pid_tab)
	{
		free_tab(path);
		free_exec_struct(exec);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	temp_list = list_word;
	exec->list_word = list_word;
	while (temp_list)
	{
		if (!change_stdin(list_word, &temp_list))
		{
			free(pid_tab);
			free_tab(path);
			free_exec_struct(exec);
			return ;
		}
		pid_tab[i] = t_exec_cmd(temp_list, exec, &fd);
		if (to_next_cmd(&temp_list))
			break ;
		i++;
	}
	wait_all_process(pid_tab, list_word, exec);
	free(pid_tab);
}
