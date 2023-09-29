#include "../../include/minishell.h"

void	clean_list(t_struct **list)
{
	t_struct *tmp;
    // t_struct *before;

    while (*list)
    {
        if (ft_strcmp((*list)->str, "<") == 0)
        {
            tmp = *list;
            *list = (*list)->next;
            delete_node(&tmp);
        }
        else
        {
            list = &((*list)->next);
        }
    }
}
