#include "../../include/minishell.h"

void	swap_node(t_struct **redir, t_struct **cmd)
{
	t_struct	*tmp;

	tmp = (*redir)->next;
	(*redir)->next = *cmd;
	tmp->next->next = (*cmd)->next;
	(*cmd)->next = tmp;
}

void	switch_to_value(t_struct **list, t_exec *exec)
{
	t_env	*env;
	char	*value;

	env = exec->env;
	while (env)
	{
		if (ft_strcmp((*list)->str + 1, env->name) == 0)
		{
			value = ft_strdup(env->value);
			free((*list)->str);
			(*list)->str = NULL;
			(*list)->str = value;
			return ;
		}
		env = env->next;
	}
}

void	change_env_var(t_struct **list, t_exec *exec)
{
	t_struct	*lst;
	t_struct	*start;

	lst = (*list);
	start = lst;
	while (lst && lst->next)
	{
		if (ft_strcmp(lst->str, "echo") == 0
			&& ft_strncmp(lst->next->str, "$", 1) == 0)
			switch_to_value(&lst->next, exec);
		lst = lst->next;
	}
	(*list) = start;
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
