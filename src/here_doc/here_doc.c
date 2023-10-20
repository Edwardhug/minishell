#include "../../include/minishell.h"

void	ft_child_here_doc(char *lim, int *fd, t_exec *exec)
{
	char	*tmp;
	char	*to_ret;

	close(fd[0]);
	to_ret = ft_calloc(1, sizeof(char));
	if (!to_ret)
		return ;
	signal(SIGINT, sigint_handler_heredoc);
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
		{
			free(to_ret);
			ft_putstr_fd(tmp, fd[1]);
			close(fd[1]);
			ft_printf("warning : wanted `%s'\n", lim);
			free_exec_struct(exec);
			exit(3);
		}
		if ((ft_strncmp(tmp, lim, ft_strlen(lim)) == 0)
			&& (ft_strlen(lim) == ft_strlen(tmp)))
		{
			ft_putstr_fd(to_ret, fd[1]);
			free(tmp);
			free(to_ret);
			close(fd[1]);
			free_exec_struct(exec);
			exit(EXIT_SUCCESS);
		}
		to_ret = ft_strjoin(to_ret, tmp);
		to_ret = ft_strjoin(to_ret, "\n");
		free(tmp);
	}
}

int	parent_here_doc(t_struct *temp_list, int *fd)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	wait(&status);
	g_error_value = status;
	signals();
	temp_list = temp_list->next;
	return (fd[0]);
	// if (temp_list->next && status == EXIT_SUCCESS)
	// {
	// 	puts("salut");
	// 	return (1);
	// }
	// else if (status == 768)
	// 	return (dup2(0, STDIN_FILENO), 1);
	// else
	// 	return (0);
}

int	here_doc(t_struct *temp_list, t_exec *exec)
{
	int		fd[2];
	int		pid;
	char	*lim;
	t_struct	*copy;

	copy = temp_list;
	if (!temp_list->next)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (0);
	}
	if (pipe(fd) == -1)
		return (0);
	while (ft_strcmp(copy->str, "<<"))
		copy = copy->next;
	lim = copy->next->str;
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		ft_child_here_doc(lim, fd, exec);
	}
	else
		return (parent_here_doc(temp_list, fd));
	return (1);
}
