/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:01:40 by lezard            #+#    #+#             */
/*   Updated: 2023/09/22 11:27:13 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	create_pipes(void)
// {
// 	//crée les pipes nécessaires quand pipe il y a
// 	return (0);
// }

//check le bon chemin à appliquer à execve
// void	find_correct_path(t_exec *exec)
// {
// 	int	i;

// 	i = 0;
// 	if (!exec->path) //c'est si on supprime le path je crois je comprend plus mon code de pipex
// 	{
// 		access_cmd(exec, i);
// 	}
// 	while (exec->path[i]) //on cherche le bon path en les testant un à un
// 	{
// 		access_cmd(exec, i);
// 		i++;
// 	}
// 	//command_not_found
// }

// //regarde si on est à la dernière commande de la ligne
// int	is_end(t_struct *temp_list)
// {
// 	while (temp_list)
// 	{
// 		if (temp_list->type == PIPE)
// 			return (0);
// 		temp_list = temp_list->next;
// 	}
// 	return (1);
// }

// //compte le nombre d'options et arguments d'une commande
// static int	nb_of_args(t_struct *lst)
// {
// 	int			i;
// 	t_struct	*tmp;

// 	tmp = lst;
// 	i = 0;
// 	while (tmp)
// 	{
// 		if (tmp->type == PIPE || tmp->type == REDIRECTION)
// 			break ;
// 		else
// 		{
// 			tmp = tmp->next;
// 			i++;
// 		}
// 	}
// 	return (i);
// }
// //récupère la commande complète avec options et arguments dans un tableau
// char	**get_cmd(t_exec *exec, t_struct *temp_list)
// {
// 	char		**cmd;
// 	int			i;
// 	int			nb_args;
// 	t_struct	*tmp;
// 	(void)exec;
// 	tmp = temp_list;
// 	nb_args = nb_of_args(temp_list);
// 	cmd = malloc(sizeof (char *) * (nb_args + 1));
// 	i = 0;
// 	while (i < nb_args)
// 	{
// 		cmd[i] = malloc(sizeof(char *) * (ft_strlen(tmp->str) + 1));
// 		if (!cmd[i])
// 			return (perror("malloc"), NULL);
// 		cmd[i] = ft_strcpy(cmd[i], tmp->str);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	cmd[i] = NULL;
// 	return (cmd);
// }

// //exécute la commande
// void	execute_command(t_exec *exec)
// {
// 	execve(exec->true_path, exec->cmd, exec->env);
// 	//free, close, wait, etc.
// }