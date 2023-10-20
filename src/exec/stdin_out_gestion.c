#include "../../include/minishell.h"

int	open_beak(t_struct *tmp, int fd_in, t_struct **temp_list)
{
	perror(tmp->str);
	dup2(fd_in, STDIN_FILENO);
	close (fd_in);
	(*temp_list) = (*temp_list)->next;
	return (-1);
}

int	open_fd_in(t_struct **temp_list)
{
	int			fd_in;
	t_struct	*tmp;

	tmp = *temp_list;
	tmp = tmp->next;
	while (tmp && tmp->next && tmp->type != CMD && tmp->type != PIPE)
	{
		fd_in = open(tmp->str, O_RDONLY);
		if (fd_in < 0)
			return (open_beak(tmp, fd_in, temp_list));
		if ((tmp->next)->type == CMD)
		{
			dup2(fd_in, STDIN_FILENO);
			close (fd_in);
			(*temp_list) = tmp->next;
			return (fd_in);
		}
		else if ((tmp->next)->type == REDIRECTION
			&& ft_strcmp((tmp->next)->str, "<") == 0)
		{
			close (fd_in);
			tmp = (tmp->next)->next;
		}
	}
	return (0);
}
