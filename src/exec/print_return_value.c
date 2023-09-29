#include "../../include/minishell.h"

void get_right_return_value(char **splited, struct stat info)
{
	if (access(splited[0], F_OK) != -1)				
	{
		if (splited[0][0] == '.' && splited[0][1] == '/')
		{
			free_tab(splited);
		 	exit(126);
		}
		else
		{
			free_tab(splited);
			exit (127);
		}
	}
	if (S_ISDIR(info.st_mode))
	{
		free_tab(splited);
		exit(128);
	}
	free_tab(splited);
	exit(127);
}

void	print_return_value(t_struct *lst)
{
	if ((ft_strncmp("$?", lst->str, 2) == 0)
			&& (ft_strlen(lst->str) == 2))
	{
		ft_putnbr_fd(g_error_value / 256, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

int	print_clean_return_value(char *str)
{
	if ((ft_strncmp("$?", str, 2) == 0)
			&& (ft_strlen(str) == 2))
	{
		ft_putnbr_fd(g_error_value / 256, 1);
		ft_putstr_fd("\n", 1);
		return (1);
	}
	return (0);
}