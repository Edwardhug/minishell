#include "../../include/minishell.h"

void	swap_node(t_struct **redir, t_struct **cmd)
{
	t_struct	*tmp;

	tmp = (*redir)->next;
	(*redir)->next = *cmd;
	tmp->next->next = (*cmd)->next;
	(*cmd)->next = tmp;
}

void	clean_redir_out(t_struct **list)
{
	t_struct	*redir;
	t_struct	*cmd;
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
				swap_node(&redir, &cmd);
				(*list) = start;
			}
			else
				redir = redir->next;
		}
		else
			redir = redir->next;
	}
}
