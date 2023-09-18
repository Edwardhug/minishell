/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:12:45 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/18 14:18:40 by lgabet           ###   ########.fr       */
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

int	get_fd_in(t_struct *list_word, t_struct *temp_list, int fd_out) // fonction pour savoir auel sera le fdin de la commande qui arrive
{
	int fd_in;

	if (t_struct_strlen(list_word) == t_struct_strlen(temp_list)) // check si c'est la premiere commande
	{
		if (list_word->type == REDIRECTION)						// verifie si c'est une redirection
		{
			if (ft_strncmp(list_word->str, "<<", 2) == 0)
				fd_in = open_fd_in(temp_list);				// l'entree c'est le heredoc mais on verra ca plus tard, (lgabet a un heredoc)
			else
				fd_in = open_fd_in(temp_list);					// l'entree c'est le fichier aui suit le ( < )
		}
		else
			fd_in = dup(0);                                          // l'entree c'est le terminal
	}
	else
		fd_in = dup(fd_out);                                         // l'infile est le stdout deja existant
	return (fd_in);
}

int	get_fd_out(t_struct *list_word, t_struct *temp_list) // fonction pour savoir quel sera le fdout de la commande qui arrive
{
	int fd_out;

	while (temp_list)
	{
		if (temp_list->type == REDIRECTION)					// verifie si le str de la node est une redirection
			if (ft_strncmp(list_word->str, ">>", 2) == 0)	// verifie si c'est une redirection qui m'efface pas ( >> )
				// la sortie sera le fichier qui suit la redirection sans l'effacer ( >> )
			else
				// la sortie sera le fichier qui suit la redirection et l'effacera ( > )
		if (temp_list->type == PIPE)						// verifie si le str de la node est une redirection
			// besoin de preparer l'utilisation du pipe
	}
	// si c'est ni une redirection, ni un pipe et qu'on arrive au bout de la liste chainee, c'est que c'est la sortie standard
	return (fd_out);
}

void exec_start(char **path, char **env, t_struct *list_word)
{
	int 		fd_in;
	int			fd_out;
	t_struct	*temp_list;

	temp_list = list_word;
	while (temp_list)
	{
		fd_in = get_fd_in(list_word, temp_list, fd_out);
		fd_out = get_fd_out(list_word, temp_list);
		exec_cmd(path, env, list_word, fd_in, fd_out);
	}
}