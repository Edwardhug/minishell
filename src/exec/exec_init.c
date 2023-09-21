#include "../../include/minishell.h"

static int	create_pipes(t_exec *exec, int i)
{
	exec->pipes[i] = malloc(sizeof(int) * 2);
	if (!exec->pipes[i])
		return (perror("malloc"), 1);
	if (pipe(exec->pipes[i]) == -1)
		return (perror("malloc"), 1);
	return (0);
}

static int	initialize_pipes(t_exec *exec, t_struct *list_word)
{
	int			i;
	int			nb_pipes;
	t_struct	*tmp;

	nb_pipes = 0;
	tmp = list_word;
	while (tmp)
	{
		if (tmp->type == PIPE)
			nb_pipes++;
		tmp = tmp->next;
	}
	exec->pipes = malloc(sizeof (int *) * nb_pipes);
	if (!exec->pipes)
		return (perror("malloc"), 1);
	i = 0;
	while (i < nb_pipes)
	{
		create_pipes(exec, i);
		i++;
	}
	return (0);
}

static int	count_all_cmds(t_struct *list_word)
{
	int			i;
	t_struct	*tmp;

	i = 0;
	tmp = list_word;
	while (tmp)
	{
		if (tmp->type == CMD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	init_params(t_exec *exec, char **path, char **env, t_struct *list_word)
{
	exec->nb_cmds = count_all_cmds(list_word);
	exec->env = env;
	exec->path = path;
	initialize_pipes(exec, list_word);
	exec->pids = malloc(sizeof(pid_t) * exec->nb_cmds);
	if (!exec->pids)
		return (perror("malloc"), 1);
	return (0);
}