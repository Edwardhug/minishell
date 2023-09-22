/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fork_gestion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:30:36 by codespace         #+#    #+#             */
/*   Updated: 2023/09/22 11:26:02 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	open_fd_in(t_struct *temp_list)									// fonction qui change de stdin pour mettre fd_in a la place
// {
// 	int	fd_in;

// 	temp_list = temp_list->next;
// 	fd_in = open(temp_list->str, O_RDONLY);
// 	if (fd_in < 0)
// 	{
// 		perror(temp_list->str);
// 	}
// 	else
// 		dup2(fd_in, STDIN_FILENO);
// 	if (fd_in != -1)
// 		close (fd_in);
// 	return (fd_in);
// }

// int change_stdin(t_struct *list_word, t_struct *temp_list) // fonction pour savoir auel sera le fdin de la commande qui arrive
// {
// 	if (t_struct_strlen(list_word) == t_struct_strlen(temp_list)) // check si c'est la premiere commande
// 	{
// 		if (list_word->type == REDIRECTION)                        // verifie si c'est une redirection
// 		{
// 			if (ft_strncmp(list_word->str, "<<", 2) == 0)
// 			{
// 				if (!here_doc(temp_list))                // l'entree c'est le heredoc mais on verra ca plus tard, (lgabet a un heredoc)
// 					return (0);
// 			}
// 			else
// 				open_fd_in(temp_list);                    // l'entree c'est le fichier qui suit le ( < )
// 		}
// 		// else
// 		//     dup2(fd_in, STDIN_FILENO);                                          // l'entree c'est le terminal
// 	}
// 	// else
// 	//     dup2(fd_in, STDIN_FILENO);                                      // l'infile est le stdout deja existant
// 	return (1);
// }