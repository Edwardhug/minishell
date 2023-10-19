#include "../../include/minishell.h"

void	swap_node(t_struct **redir, t_struct **cmd)
{
	t_struct	*tmp;

	tmp = (*redir)->next;
	(*redir)->next = *cmd;
	tmp->next->next = (*cmd)->next;
	(*cmd)->next = tmp;
}

char	*dup_without_space(char *str)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	copy = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!copy)
		return (NULL);
	while(str[i])
	{
		if (str[i] == ' ')
		{
			copy[j] = str[i];
			j++;
			i++;
			while (str[i] && str[i] == ' ')
				i++;
		}
		copy[j] = str[i];
		j++;
		i++;
	}
	return (copy);
}

void    switch_to_value(t_struct **list, t_exec exec)
{
    char        *value;
	t_struct	*copy;

    while (exec.env)
    {
		if ((*list)->str && ft_strcmp((*list)->str, "echo") == 0
			&& ft_strcmp((*list)->next->str + 1, exec.env->name) == 0)
		{
			value = dup_without_space(exec.env->value);
			if (!value)
				return ;
            free((*list)->next->str);
            (*list)->next->str = NULL;
            (*list)->next->str = value;
            return ;
		}
        else if (ft_strcmp((*list)->next->str + 1, exec.env->name) == 0)
        {
            value = ft_strdup(exec.env->value);
			if (!value)
				return ;
            free((*list)->next->str);
            (*list)->next->str = NULL;
            (*list)->next->str = value;
            return ;
        }
        exec.env = exec.env->next;
    }
	if (ft_strncmp((*list)->next->str, "$?", 2)
		&& (*list)->next->str[1])
	{	
		copy = (*list)->next;
		(*list)->next = (*list)->next->next;
		free(copy->str);
		free(copy);
	}
	if ((*list)->str == NULL && (*list)->next && (*list)->next->str)
		(*list) = (*list)->next;
}

int    change_env_var(t_struct **list, t_exec *exec)
{
    t_struct    *lst;
    t_struct    *start;

    lst = (*list);
    start = lst;
    while (lst && lst->next)
    {
        if (ft_strncmp(lst->next->str, "$", 1) == 0
            && (!lst->str || lst->str[1]))
                switch_to_value(&lst, *exec);
        lst = lst->next;
    }
    (*list) = start;
	if (!(*list)->next)
		return (0);
	return (1);
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
