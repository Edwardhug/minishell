#include "../../../include/minishell.h"

void	show_env_var(t_exec *exec, char *arg)
{
	t_env	*tmp;

	tmp = exec->lst_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, arg) == 0)
		{
			ft_printf("%s", tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

int	is_env_var(t_exec *exec, char *arg)
{
	t_env	*tmp;

	tmp = exec->lst_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, arg + 1) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_echo(char **cmd, t_exec *exec)
{
	int	dash_n; //sert de booléen
	int	i;

	i = 1;
	if (exec->nb_cmds > 1 && print_clean_return_value(cmd[1]))
		exit(0);
	else if (print_clean_return_value(cmd[1]))
		return (2);
		
	if (ft_strcmp(cmd[1], "-n") == 0) //on regarde si on a le -n pour le saut à la ligne
	{
		i++;
		dash_n = 0;
	}
	else
		dash_n = 1;
	while (cmd[i])
	{
		if (is_env_var(exec, cmd[i]))
			show_env_var(exec, cmd[i] + 1);
		else
			ft_printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL) //si on est pas au dernier argument, on met un espace.
			ft_printf(" ");
		i++;
	}
	if (dash_n) //si on a pas de -n on va à la ligne
		ft_printf("\n");
	if (exec->nb_cmds > 1)
		exit(0);
	return (0);
}