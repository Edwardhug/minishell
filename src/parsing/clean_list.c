#include "../../include/minishell.h"


void swap_nodes(t_struct **cmd, t_struct **tmp)
{
	char	*copy;
	int		enu;

	copy = (*cmd)->str;
	(*cmd)->str = (*tmp)->str;
	(*tmp)->str = copy;
	enu = (*cmd)->type;
	(*cmd)->type = (*tmp)->type;
	(*tmp)->type = enu;
}

void put_list_in_order(t_struct **lst)
{
	t_struct  *cmd;
	t_struct *current = *lst;

	while (current->next)
	{
		if (current->type == CMD)
			cmd = current->next;
		if (ft_strcmp(current->str, "<") == 0)
		{
			// ft_printf("cmd = %s\nlst = %s\n", cmd->str, current->str);
			swap_nodes(&cmd, &current);
			swap_nodes(&(cmd->next), &(current->next));
		}
		current = current->next;
	}
}

void	clean_list(t_struct **list)
{
	t_struct *tmp;
    // t_struct *before;

	put_list_in_order(list);
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
