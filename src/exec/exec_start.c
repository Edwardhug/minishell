/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:08:24 by lezard            #+#    #+#             */
/*   Updated: 2023/09/22 19:26:22 by lgabet           ###   ########.fr       */
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

void begin_execution(char **path, char **env, t_struct *list_word)
{
	t_struct	*temp_list;
	int			pid;

	pid = fork();
	if (pid == 0)
	{
		(void)path;
		temp_list = list_word;
		while (temp_list)
		{
			change_stdin(list_word, temp_list);
			if (have_pipe(temp_list))
				t_exec_cmd(temp_list, env);
			else
				exec_last_cmd(temp_list, env);
			while (temp_list->next && temp_list->type != PIPE)
			{
				temp_list = temp_list->next;
			}
			if (temp_list->type == PIPE)
				temp_list = temp_list->next;
		}
	}
	else
		waitpid(pid, NULL, WUNTRACED);
}
