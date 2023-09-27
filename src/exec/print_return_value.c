#include "../../include/minishell.h"

t_struct	*print_return_value(t_struct *lst)
{
	if ((ft_strncmp("$?", lst->str, 2) == 0)
			&& (ft_strlen(lst->str) == 2))
	{
		ft_printf("%d: ", error_value);
		if (lst->next)
			lst = lst->next;
	}
	return (lst);
}