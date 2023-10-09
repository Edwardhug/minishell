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

int	ft_echo(char **cmd, t_exec *exec)
{
	int	dash_n; //sert de booléen
	int	i;
	int	j;

	i = 1;
	if (ft_strcmp(cmd[1], "-n") == 0) //on regarde si on a le -n pour le saut à la ligne
	{
		i++;
		dash_n = 0;
	}
	else
		dash_n = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '$')
				print_var(cmd, &i, &j, exec);
			else
				ft_printf("%c", cmd[i][j]);
			j++;
		}
		if (cmd[i + 1] != NULL) //si on est pas au dernier argument, on met un espace.
			ft_printf(" ");
		i++;
	}
	if (dash_n) //si on a pas de -n on va à la ligne
		ft_printf("\n");
	exit(0);
}