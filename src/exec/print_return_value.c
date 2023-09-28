#include "../../include/minishell.h"

void	print_return_value(t_struct *lst)
{
	if ((ft_strncmp("$?", lst->str, 2) == 0)
			&& (ft_strlen(lst->str) == 2))
	{
		ft_putnbr_fd(error_value / 256, 0);
		ft_putstr_fd(": command not found\n", 0);
		exit(127);
	}
}