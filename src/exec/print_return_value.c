#include "../../include/minishell.h"

void	print_return_value(t_struct *lst)
{
	if ((ft_strncmp("$?", lst->str, 2) == 0)
			&& (ft_strlen(lst->str) == 2))
	{
		ft_putnbr_fd(g_error_value / 256, 0);
		ft_putstr_fd(": command not found\n", 0);
		exit(127);
	}
}

int	print_clean_return_value(char *str)
{
	if ((ft_strncmp("$?", str, 2) == 0)
			&& (ft_strlen(str) == 2))
	{
		ft_putnbr_fd(g_error_value / 256, 0);
		ft_putstr_fd("\n", 0);
		return (1);
	}
	return (0);
}