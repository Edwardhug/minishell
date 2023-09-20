/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:01:40 by lezard            #+#    #+#             */
/*   Updated: 2023/09/20 14:14:14 by codespace        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	create_pipes(void)
// {
// 	//crée les pipes nécessaires quand pipe il y a
// 	return (0);
// }

static int	nb_of_args(t_struct *lst)
{
	int			i;
	t_struct	*tmp;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			break ;
		else
		{
			tmp = tmp->next;
			i++;
		}
	}
	return (i);
}

//récupère la commande complète avec options et arguments dans un tableau
char	**get_cmd(t_exec *exec, t_struct *temp_list)
{
	char		**cmd;
	int			i;
	int			nb_args;
	t_struct	*tmp;

	(void)exec;
	tmp = temp_list;
	nb_args = nb_of_args(temp_list);
	cmd = malloc(sizeof (char *) * (nb_args + 1));
	i = 0;
	while (i < nb_args)
	{
		cmd[i] = malloc(sizeof(char *) * (ft_strlen(tmp->str) + 1));
		if (!cmd[i])
			return (perror("malloc"), NULL);
		cmd[i] = ft_strcpy(cmd[i], tmp->str);
		tmp = tmp->next;
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

void	execute_command(t_exec *exec)
{
	execve(exec->true_path, exec->cmd, exec->env);
	//free, close, wait, etc.
}