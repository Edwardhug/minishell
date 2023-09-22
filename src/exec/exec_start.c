/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:08:24 by lezard            #+#    #+#             */
/*   Updated: 2023/09/22 11:48:35 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	access_cmd(t_exec *exec, int i)
// {
// 	char	*tmp;

// 	tmp = NULL;
// 	if (ft_strnstr(exec->cmd[0], "/", ft_strlen(exec->cmd[0])) != NULL)
// 	{
// 		exec->true_path = ft_strdup(exec->cmd[0]);
// 		if (!(exec->true_path))
// 			perror("strdup");
// 	}
// 	else
// 	{
// 		tmp = ft_strjoin(exec->path[i], "/");
// 		if (!tmp)
// 			perror("malloc");
// 		exec->true_path = ft_strjoin(tmp, exec->cmd[0]);
// 		if (!(exec->true_path))
// 			perror("malloc");
// 		free(tmp);
// 	}
// 	if (access(exec->true_path, R_OK) != -1)
// 		execute_command(exec);
// 	//free tout ça
// }

int	is_builtin(char	**cmd)
{
	if (ft_strnstr(cmd[0], "cd", 2) != NULL)
	{
		printf("on trouve cd dans les commandes\n");
		return (ft_cd(cmd), 1);
	}
	return (0);
}


// int	exec_cmd(t_exec *exec, t_struct *list_word, t_struct *temp_list)
// {
// 	(void)list_word;
// 	//pipe
// 	//fork
// 	exec->cmd = get_cmd(exec, temp_list);
// 	if (!exec->cmd)
// 		return (perror("malloc"), 1);
// 	if (is_builtin(exec) == 1)
// 	{
// 		//builtin
// 		return(0);
// 	}
// 	else
// 	{
// 		//commande normale
// 		find_correct_path(exec);
// 	}
// 	return (0);
// /*
// 	On fait un tableau de fork pour stocker les p ids.
// 	Si on est dans le processus enfant, on regarde si builtins ou commande normale.
// 	Si builtins on redirige.
// 	Si commande normale on cherche le path puis access puis execve.

// 	mais pour moi il faut fork avant la boucle.
// */
// }

void begin_execution(char **path, char **env, t_struct *list_word)
{
	t_struct	*temp_list;

	(void)path;
	temp_list = list_word;
	while (temp_list)
	{
		change_stdin(list_word, temp_list);
		t_exec_cmd(temp_list, env);
		while (temp_list->next && temp_list->type != PIPE)
		{
			temp_list = temp_list->next;
		}
		if (temp_list->type == PIPE)
			temp_list = temp_list->next;
		else
			break ;
	}
}
