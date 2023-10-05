#include "../../../include/minishell.h"

static void	ft_swap(t_env *node1, t_env *node2)
{
	char	*tmp_name;
	char	*tmp_value;

	if (node1 == NULL || node1->next == NULL)
		return ;
	if (node2 == NULL || node2->next == NULL)
		return ;
	tmp_name = node1->name;
    tmp_value = node1->value;
    node1->name = node2->name;
    node1->value = node2->value;
    node2->name = tmp_name;
    node2->value = tmp_value;
}

static void	sort_list(t_exec *exec)
{
	int		swapped;
	t_env	*head;
	t_env	*last_ptr;

	last_ptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		head = exec->export;
		while (head && head->next != last_ptr)
		{
			if (ft_strcmp(head->name, head->next->name) > 0)
			{
				ft_swap(head, head->next);
				swapped = 1;
			}
			head = head->next;
		}
		last_ptr = head;
	}
}

static void	show_export(t_exec *exec)
{
	t_env	*tmp;

	sort_list(exec);
	tmp = exec->export;
	while (tmp)
	{
		ft_printf("declare -x ");
		ft_printf("%s", tmp->name);
		if (tmp->value != NULL)
		{
			ft_printf("=");
			ft_printf("%s", tmp->value);
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
}

	/*
	-'export MYEXISTENTVAR': je ne fais rien
	-'export MYNONEXISTENTVAR': je crée la variable vide et la met dans export.
	-'export MYEXISTENTVAR=NEWVALUE': je remplace la valeur dans export et dans env.
	-'export MYNONEXISTENTVAR=VALUE': je crée une nouvelle variable d'environnement à la fin de la liste env et dans export.
	*/

// static int	what_to_do(char **cmd, t_exec *exec)
// {
// 	t_env	*tmp;
// 	t_env	*lst_args;
// 	t_env	*args_tmp;

// 	lst_args = env_double_char_into_lst(cmd + 1);	//on met les args dans une liste pour comparer plus facilement.
// 	while (lst_args)
// 	{
// 		tmp = exec->export;
// 		args_tmp = lst_args;
// 		while (tmp)
// 		{
// 			if (ft_strcmp(tmp->name, args_tmp->name) == 0)
// 			{
// 				if (args_tmp->value == NULL || args_tmp->value[0] == '\0') //variable trouvée mais pas de valeur = on fait rien
// 					ft_printf("%s existe mais pas de value\n", args_tmp->name);
// 				else	//variable trouvée et nouvelle valeur à mettre
// 				{
// 					ft_printf("%s existe et a une value\n", args_tmp->name);
// //					change_var(args_tmp, exec);
// 				}
// 				break ;
// 			}
// 			tmp = tmp->next;
// 		}
// 		if (!tmp)
// 		{
// 			ft_printf("%s n'existe pas\n", args_tmp->name);
// //			create_var(cmd, exec); //la variable n'a pas été trouvée donc on la crée
// 		}
// 		lst_args = lst_args->next;
// 	}
// 	//free env list
// 	return (0);
// }

int	ft_export(char **cmd, t_exec *exec)
{
	int	nb_args;

	while (cmd[nb_args])
		nb_args++;
	if (nb_args == 1)
		show_export(exec);
	// else
	// {
	// 	what_to_do(cmd, exec);
	// }
	if (exec->nb_cmds > 1)
		exit(0);
	return (0);
}

/*
-CHECK 'export' seul: j'affiche toutes les variables d'environnement de export.

export doit toujours être trié par ordre ascii.
*/

// static int	create_var(char **cmd, t_exec *exec)
// {
// 	(void)cmd;
// 	(void)exec;
// 	return (0);
// }

// static int	export_var(char *arg, t_exec *exec)
// {
// 	(void)arg;
// 	(void)exec;
// 	return (0);
// }

// static int	show_var(char *arg, t_exec *exec)
// {
// 	(void)arg;
// 	(void)exec;
// 	return (0);
// }