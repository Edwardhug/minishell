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

void	clean_redir_out(t_struct **list)
{
	t_struct	*redir;
	t_struct	*cmd;
	t_struct	*tmp;
	t_struct	*start;

	redir = *list;
	start = redir;
	while (redir && redir->next && redir->next->next)
	{
		if (redir->next->type == REDIRECTION
			&& ft_strncmp(redir->next->str, ">", 1) == 0)
		{
			cmd = redir->next;
			while (cmd && cmd->next && cmd->type != CMD && cmd->type != PIPE)
				cmd = cmd->next;
			if (cmd->type == CMD)
			{
				tmp = redir->next;
				redir->next = cmd;
				tmp->next->next = cmd->next;
				cmd->next = tmp;
				(*list) = start;
			}
			else
				redir = redir->next;
		}
		else
			redir = redir->next;
	}
}

void	put_infile_in_order(t_struct **list)
{
	// t_struct	*f_redir;
	// t_struct	*l_redir;

	// if ((*list)->next->type == REDIRECTION
	// 	&& ft_strcmp((*list)->next->str, "<") == 0
	// 	&& (*list)->next->next)
	// 	f_redir = ((*list)->next->next);
	// else
	// {
	// 	clean_redir_out(list);
	// 	return ;
	// }
	// l_redir = f_redir;
	// while (l_redir->next && l_redir->next->type != CMD
	// 	&& l_redir->next->type != PIPE)
	// 	l_redir = l_redir->next;
	// swap_nodes(&f_redir, &l_redir);
	clean_redir_out(list);
}

int	cmd_is_before(t_struct *cmd, t_struct *redir)
{
	while (cmd)
	{
		if (cmd == redir)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

void	clean_list(t_struct **list)
{
	// t_struct	*tmp;
	// t_struct	*copy;
	// t_struct	*b_cmd;

	// copy = *list;
	// while (copy && copy->next)
	// {
	// 	if ((copy->next)->type == CMD)
	// 		b_cmd = copy;
	// 	if ((copy->next)->type == REDIRECTION
	// 		&& cmd_is_before(b_cmd, copy)
	// 		&& ft_strcmp((copy->next)->str, "<") == 0
	// 		&& ((copy->next)->next)->type == FILES
	// 		&& copy->type != ENUM_NULL)
	// 	{
	// 		tmp = copy->next;
	// 		copy->next = copy->next->next->next;
	// 		tmp->next->next = b_cmd->next;
	// 		b_cmd->next = tmp;
	// 		*list = b_cmd;
	// 		// print_list(*list);
	// 		// exit (0);
	// 	}
	// 	else
	// 		copy = copy->next;
	// }
	put_infile_in_order(list);
}
