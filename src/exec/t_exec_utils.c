#include "minishell.h"

void	print_error(char **splited_cmd, char **all_path, int i)
{
	if (i == 1)
		ft_putstr_fd("command not found: ", 2);
	else
		ft_putstr_fd("no such file or directory: ", 2);
	ft_putstr_fd(splited_cmd[0], 2);
	ft_putstr_fd("\n", 2);
	// free_tab(splited_cmd);
	free_tab(all_path);
}