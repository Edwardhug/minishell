#include "../../include/minishell.h"

int	open_fd_in(t_struct **temp_list)									// fonction qui change de stdin pour mettre fd_in a la place
{
	int	fd_in;
	t_struct	*tmp;

	tmp = *temp_list;
	tmp = tmp->next;
	while (tmp && tmp->next && tmp->type != CMD && tmp->type != PIPE)
	{
		fd_in = open(tmp->str, O_RDONLY);
		if (fd_in < 0)
		{
			perror(tmp->str);
			dup2(fd_in, STDIN_FILENO);
			close (fd_in);
			(*temp_list) = (*temp_list)->next;
			return (-1);
		}
		if ((tmp->next)->type == CMD)
		{
			dup2(fd_in, STDIN_FILENO);
			close (fd_in);
			(*temp_list) = tmp->next;
			return (fd_in);
		}
		else if ((tmp->next)->type == REDIRECTION && ft_strcmp((tmp->next)->str, "<") == 0)
		{
			close (fd_in);
			tmp = (tmp->next)->next;
		}
	}
	return (0);
}

int change_stdin(t_struct *list_word, t_struct **temp_list) // fonction pour savoir quel sera le fdin de la commande qui arrive
{
	t_struct	*copy;

	copy = (*temp_list);
	while (copy && copy->type != PIPE)
	{
		if (ft_strcmp(copy->str, "<<") == 0)
			return (here_doc(*temp_list));
		copy = copy->next;
	}
	return (1);
	(void)list_word;
}