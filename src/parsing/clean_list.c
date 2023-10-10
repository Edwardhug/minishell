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

// void put_list_in_order(t_struct **lst)
// {
// 	t_struct  *cmd;
// 	t_struct *current = *lst;

// 	while (current->next)
// 	{
// 		if (current->type == CMD)
// 			cmd = current->next;
// 		if (ft_strcmp(current->str, "<") == 0)
// 		{
// 			// ft_printf("cmd = %s\nlst = %s\n", cmd->str, current->str);
// 			swap_nodes(&cmd, &current);
// 			swap_nodes(&(cmd->next), &(current->next));
// 		}
// 		current = current->next;
// 	}
// }

// void	clean_list(t_struct **list)
// {
// 	t_struct *tmp;
//     // t_struct *before;

// 	put_list_in_order(list);
//     while (*list)
//     {
//         if (ft_strcmp((*list)->str, "<") == 0)
//         {
//             tmp = *list;
//             *list = (*list)->next;
//             delete_node(&tmp);
//         }
//         else
//         {
//             list = &((*list)->next);
//         }
//     }
// }

// void	clean_list(t_struct **list)
// {
// 	t_struct	*tmp;
// 	t_struct	*cmd;
// 	t_struct	*redir;
// 	t_struct	*file;

// 	tmp = (*list);
// 	print_list(tmp);
// 	while (tmp && tmp->next)
// 	{
// 		if (tmp->type == CMD)
// 			cmd = tmp;
// 		else if (tmp->type == PIPE)
// 			cmd = tmp;
// 		redir = tmp;
// 		file = tmp->next;
// 		if (cmd->type == CMD
// 			&& redir->type == REDIRECTION
// 			&& ft_strcmp(redir->str, "<") == 0
// 			&& file->type == FILES)
// 		{
// 			swap_nodes(&cmd, &redir);
// 			swap_nodes(&cmd->next, &file);
// 		}
// 		else
// 			tmp = tmp->next;
// 	}
// 	print_list(*list);
// }

void	clean_list(t_struct **list)
{
	t_struct	*tmp;
	t_struct	*copy;
	t_struct	*b_cmd;

	copy = *list;
	while (copy && copy->next)
	{
		// ft_printf("yoooo\n");
		if ((copy->next)->type == CMD)
			b_cmd = copy;
		// ft_printf("(copy->next)->type  %d\n", (copy->next)->type);
		if ((copy->next)->type == REDIRECTION
			&& ft_strcmp((copy->next)->str, "<") == 0
			&& ((copy->next)->next)->type == FILES)
		{
			// ft_printf("copy = %s\n", tmp->next->str);
			tmp = copy->next;
			copy->next = copy->next->next->next;
			tmp->next->next = b_cmd->next;
			b_cmd->next = tmp;
			*list = b_cmd;
			return ;
		}
		else
			copy = copy->next;
	}
	(void)b_cmd;
	(void)tmp;
}
