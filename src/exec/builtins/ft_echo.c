#include "../../../include/minishell.h"

void	show_env_var(t_exec *exec, char *arg, int *j)
{
	t_env	*tmp;

	tmp = exec->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, arg + 1, ft_strlen(tmp->name)) == 0)
		{
			ft_printf("%s", tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	(*j) = (*j) + ft_strlen(tmp->name);
}

int	is_env_var(t_exec *exec, char *arg)
{
	t_env	*tmp;
	int		i;

	tmp = exec->env;
	i = 1;
	if (arg[0] == '\'' && arg[1] == '$')
	{
		while (arg[i] && arg[i] != '\'')
		{
			ft_printf("%c", arg[i]);
			i++;
		}
		return (1);
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->name, arg + 1, ft_strlen(tmp->name)) == 0)
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	print_var(char **cmd, int *i, int *j, t_exec *exec)
{
	if (cmd[(*i)][(*j) + 1] == '?')
	{
		print_clean_return_value(cmd[(*i)] + (*j));
		(*j)++;
	}
	else if (is_env_var(exec, cmd[(*i)] + (*j)))
		show_env_var(exec, cmd[(*i)] + (*j), j);
	else
		ft_printf("$");
}

static int	is_dash_n(char *arg)
{
	int	i;

	i = 1;
	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

int	ft_echo(char **cmd, t_exec *exec)
{
	int	dash_n;
	int	newline;
	int	i;
	int	j;
	int	simple_quote;

	i = 1;
	newline = 0;
	while (cmd[i])
	{
		dash_n = is_dash_n(cmd[i]);
		if (!dash_n)
		{
			newline++;
			i++;
		}
		else
			break ;
	}
	while (cmd[i])
	{
		simple_quote = 0;
		j = 0;
		if (cmd[i][j] == '\'')
			simple_quote = 1;
		while (cmd[i][j + simple_quote + simple_quote])
		{
			if (cmd[i][j] == '$' && simple_quote == 0)
				print_var(cmd, &i, &j, exec);
			else
				ft_printf("%c", cmd[i][j + simple_quote]);
			j++;
		}
		if (cmd[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (!newline)
		ft_printf("\n");
	free_exec_fork(exec);
	exit(0);
}