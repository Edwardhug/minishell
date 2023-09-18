/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:12:45 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/18 15:26:00 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_fd_in(t_struct *temp_list)								// fonction qui change de stdin pour mettre fd_in a la place
{
	int	fd_in;

	temp_list = temp_list->next;
	fd_in = open(temp_list->str, O_RDONLY);
	if (fd_in < 0)
		perror(temp_list->str);
	else
		dup2(fd_in, STDIN_FILENO);
	if (fd_in != -1)
		close (fd_in);
	return (fd_in);
}

int	get_fd_in(t_struct *list_word, t_struct *temp_list) // fonction pour savoir auel sera le fdin de la commande qui arrive
{
	int fd_in;

	if (t_struct_strlen(list_word) == t_struct_strlen(temp_list)) // check si c'est la premiere commande
	{
		if (list_word->type == REDIRECTION)						// verifie si c'est une redirection
		{
			if (ft_strncmp(list_word->str, "<<", 2) == 0)
				fd_in = open_fd_in(temp_list);				// l'entree c'est le heredoc mais on verra ca plus tard, (lgabet a un heredoc)
			else
				fd_in = open_fd_in(temp_list->next);					// l'entree c'est le fichier qui suit le ( < )
		}
		else
			fd_in = dup(STDIN_FILENO);                                          // l'entree c'est le terminal
	}
	else
		fd_in = dup(STDIN_FILENO);                                      // l'infile est le stdout deja existant
	return (fd_in);
}

int	is_end(t_struct *temp_list)
{
	while (temp_list)
	{
		if (temp_list->type == PIPE)
			return (0);
		temp_list = temp_list->next;
	}
	return (1);
}

void exec_start(char **path, char **env, t_struct *list_word)
{
	int 		fd_in;
	t_struct	*temp_list;

	temp_list = list_word;
	while (temp_list)
	{
		fd_in = get_fd_in(list_word, temp_list);
		if (is_end(temp_list))												// check si il y a d'autres cmd ou si c'est la derniere ( si il y a un pipe quoi)
		{
			last_exec();										// si c'est la derniere commande on fait un dernier execv
			return ();
		}
		else
			exec_cmd(path, env, list_word, fd_in);		// si c'est pas la derniere on applique la cmd sur le STDIN et on change le STDOUT
		while (temp_list->type != PIPE)
			temp_list = temp_list->next;
		temp_list = temp_list->next;
	}
}
