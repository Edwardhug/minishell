/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lezard <lezard@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:01:40 by lezard            #+#    #+#             */
/*   Updated: 2023/09/19 14:44:33 by lezard           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	create_pipes(void)
// {
// 	//crée les pipes nécessaires quand pipe il y a
// 	return (0);
// }

char	**get_cmd(t_exec *exec, t_struct *temp_word)
{
	char	**cmd;

	(void)exec;
	(void)temp_word;
	cmd = malloc(sizeof (char *) * 2);
	//récupère la commande complète avec options et arguments
	return (cmd);
}

// void	get_correct_path()
// {
// 	//récupérer le bon chemin en testant avec access_cmd
// }

// void	access_cmd(t_exec *exec, char **args)
// {
// 	//trouver le bon chemin avec access
	
// }

// void	execute_command(t_exec *exec, char **args)
// {
// 	execve(exec->true_path, args, exec->env);
// 	//execute avec execve et free, ferme etc.
// }