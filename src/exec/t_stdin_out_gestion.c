#include "../../include/minishell.h"

int	open_fd_in(t_struct **temp_list)									// fonction qui change de stdin pour mettre fd_in a la place
{
	int	fd_in;
	t_struct	*tmp;

	tmp = *temp_list;
	tmp = tmp->next;
	fd_in = open(tmp->str, O_RDONLY);
	if (fd_in < 0)
	{
		perror(tmp->str);
		// ft_printf("%s\n", tmp->str);
		while (temp_list && (*temp_list)->type != PIPE)
			(*temp_list) = (*temp_list)->next;
		if ((*temp_list)->type == PIPE)
			(*temp_list) = (*temp_list)->next;
		g_error_value = 256;
	}
	else
		dup2(fd_in, STDIN_FILENO);
	if (fd_in != -1)
		close (fd_in);
	return (fd_in);
}

int change_stdin(t_struct *list_word, t_struct **temp_list) // fonction pour savoir auel sera le fdin de la commande qui arrive
{
	if (t_struct_strlen(list_word) == t_struct_strlen(*temp_list)) // check si c'est la premiere commande
	{
		if (list_word->type == REDIRECTION)                        // verifie si c'est une redirection
		{
			if (ft_strncmp(list_word->str, "<<", 2) == 0)
			{
				if (!here_doc(*temp_list))                // l'entree c'est le heredoc mais on verra ca plus tard, (lgabet a un heredoc)
					return (0);
			}
			else
				open_fd_in(temp_list);                    // l'entree c'est le fichier qui suit le ( < )
		}
		// else
		//     dup2(fd_in, STDIN_FILENO);                                          // l'entree c'est le terminal
	}
	// else
	//     dup2(fd_in, STDIN_FILENO);                                      // l'infile est le stdout deja existant
	return (1);
}