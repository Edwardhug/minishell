/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:58:02 by jrenault          #+#    #+#             */
/*   Updated: 2023/10/20 22:04:15 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	t_size_cmd(t_struct *temp_list)
{
	int	i;

	i = 0;
	while (temp_list && temp_list->type != REDIRECTION
		&& temp_list->type != PIPE)
	{
		i++;
		temp_list = temp_list->next;
	}
	return (i);
}

void	free_dup_str(char **str, t_exec *exec, int i)
{
	while (--i > 0)
		free(str[i]);
	free(str);
	free_stuff_error(exec, NULL, "malloc error\n", -1);
}

char	*join_tmp_and_secure(char **all_path, int i, t_exec *exec)
{
	char	*tmp;

	tmp = ft_strjoin(all_path[i], "/");
	if (!tmp)
		free_stuff_error(exec, NULL, "malloc error\n", -1);
	return (tmp);
}

void	execute_execve(char **splited_cmd, t_exec *exec,
	t_struct *temp_list, char *path_cmd)
{
	execve(path_cmd, splited_cmd, exec->char_env);
	free_tab(splited_cmd);
	free(path_cmd);
	free_tab(exec->char_env);
	if (errno == 13)
	{
		if (temp_list->str[0] == '/')
			free_stuff_error(exec, NULL, "no such file or directory\n", 126);
		else
			free_stuff_error(exec, NULL, "command not found\n", 126);
	}
	else
	{
		if (temp_list->str[0] == '/')
			free_stuff_error(exec, NULL, "no such file or directory\n", 127);
		else
			free_stuff_error(exec, NULL, "command not found\n", 127);
	}
}
