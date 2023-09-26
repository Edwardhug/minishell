/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:08:24 by lezard            #+#    #+#             */
/*   Updated: 2023/09/26 18:54:41 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char	**cmd)
{
	if (ft_strnstr(cmd[0], "cd", 2) != NULL)
	{
		printf("on trouve cd dans les commandes\n");
		return (ft_cd(cmd), 1);
	}
	return (0);
}

int have_pipe(t_struct *temp_list)
{
	while (temp_list->next && temp_list->type != PIPE)
		temp_list = temp_list->next;
	if (temp_list->type == PIPE)
		return (1);
	return (0);
}

int	number_of_cmd(t_struct *list_word)
{
	int i;

	i = 1;
	while (list_word->next)
	{
		if (list_word->type == PIPE)
			i++;
		list_word = list_word->next;
	}
	return (i);
}

void	wait_all_process(int *pid, t_struct *list_word)
{
	int cmd_to_finish;
	int	i;
	sig_t	old_signal[2];

	cmd_to_finish = number_of_cmd(list_word);
	i = 0;
	old_signal[0] = signal(SIGINT, sigint_handler_in_process);
	old_signal[1] = signal(SIGQUIT, sigquit_handler_in_process);
	while (i <= cmd_to_finish)
	{
		waitpid(pid[i], NULL, WUNTRACED);
		i++;
	}
	signal(SIGINT, old_signal[0]);		// signal ctrl c
	signal(SIGQUIT, old_signal[1]);		// signal ctrl backslash
}

void begin_execution(char **path, char **env, t_struct *list_word)
{
	int	pid_tab[number_of_cmd(list_word)];
	int	i;
	t_struct	*temp_list;

		i = 0;
		(void)path;
		temp_list = list_word;
		while (temp_list)
		{
			if (!change_stdin(list_word, temp_list))
				return ;
			pid_tab[i] = t_exec_cmd(temp_list, env);
			while (temp_list->next && temp_list->type != PIPE)
			{
				temp_list = temp_list->next;
			}
			if (temp_list->type == PIPE)
				temp_list = temp_list->next;
			else
				break ;
			i++;
		}
		wait_all_process(pid_tab, list_word);
}
