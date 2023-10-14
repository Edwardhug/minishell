#include "../../include/minishell.h"

int	open_fd_in_(t_struct *lst)
{
	int	fd_in;

	fd_in = open(lst->str, O_RDONLY);
	if (fd_in < 0)
	{
		perror(lst->str);
		exit(1);
	}
	return (fd_in);
}

int	open_fd_out(t_struct *lst)
{
	int	fd_out;

	fd_out = 1;
	if (!ft_strcmp(lst->str, ">>"))
	{
		lst = lst->next;
		fd_out = open(lst->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (!ft_strcmp(lst->str, ">"))
	{
		lst = lst->next;
		fd_out = open(lst->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd_out < 0)
	{
		perror(lst->str);
		exit(1);
	}
	return (fd_out);
}

void	change_std(t_fd *tfd, t_struct *lst, int fd)
{
	t_fd	cfd;

	while (lst && lst->next && lst->type != PIPE)
	{
		if (ft_strcmp(lst->str, "<") == 0)
		{
			cfd.fd_in = open_fd_in_(lst->next);
			lst = lst->next;
		}
		else if (ft_strcmp(lst->str, ">") == 0
			|| ft_strcmp(lst->str, ">>") == 0)
		{
			cfd.fd_out = open_fd_out(lst);
			lst = lst->next;
		}
		lst = lst->next;
	}
	if (lst && lst->type == PIPE)
		dup2(fd, STDOUT_FILENO);
	dup2(cfd.fd_out, STDOUT_FILENO);
	close (cfd.fd_out);
	close (fd);
	dup2(cfd.fd_in, STDIN_FILENO);
	close (cfd.fd_in);
	(*tfd) = cfd;
}
