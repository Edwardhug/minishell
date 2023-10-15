#include "../../include/minishell.h"

void	print_error(char **splited_cmd, char **all_path, int i)
{
	if (i == 1)
		ft_putstr_fd("command not found: ", 2);
	else
		ft_putstr_fd("no such file or directory: ", 2);
	ft_putstr_fd(splited_cmd[0], 2);
	ft_putstr_fd("\n", 2);
	free_tab(all_path);
}

void	change_outfile(t_struct **temp_list, int *fd)
{
	if (!ft_strcmp((*temp_list)->str, ">>"))
	{
		(*temp_list) = (*temp_list)->next;
		(*fd) = open((*temp_list)->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (!ft_strcmp((*temp_list)->str, ">"))
	{
		(*temp_list) = (*temp_list)->next;
		(*fd) = open((*temp_list)->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
}
