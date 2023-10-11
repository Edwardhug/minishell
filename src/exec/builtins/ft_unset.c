#include "../../../include/minishell.h"

static void	ft_lstdelete_node(t_exec *exec, t_env *node_to_delete, int which_lst)
{
	t_env *previous;
	t_env *current;

	previous = NULL;
	if (which_lst == 0)
		current = exec->env;
	else
		current = exec->export;
	while (current)
	{
		if (current == node_to_delete)
		{
			if (previous)
			{
				previous->next = current->next;
			}
			else
			{
				if (which_lst == 0)
					exec->env = current->next;
				else
					exec->export = current->next;
			}
			free(current->name);
			free(current->value);
			free(current);
			break ;
		}
		previous = current;
		current = current->next;
	}
}

int	ft_unset(char **cmd, t_exec *exec)
{
	t_env	*tmp;
	t_env	*tmp2;
	int		i;

	i = 1;
	while (cmd[i])
	{
		tmp = exec->env;
		while (tmp)
		{
			if (ft_strcmp(cmd[i], tmp->name) == 0)
			{
				ft_lstdelete_node(exec, tmp, 0);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	i = 1;
	while (cmd[i])
	{
		tmp2 = exec->export;
		while (tmp)
		{
			if (ft_strcmp(cmd[i], tmp2->name) == 0)
			{
				ft_lstdelete_node(exec, tmp2, 1);
				break ;
			}
			tmp2 = tmp2->next;
		}
		i++;
	}
	exit (0);
}

/*unset détruit la ou les variables d'environnement dont le nom a
été passé en argument $var.
à l'intérieur du fonction le comportement varie
suivant le type de variable qu'on veut détruire.
Si variable globale détruite depuis une fonction,
seule la variable locale sera détruite.
la variable globale gardera la valeur acquise avant
l'appel à unset

si je fais unset et que l'argument que je donne n'est pas bon ou même que je ne donne aucun arguments, il ne se passe rien.
si je fais unset PATH par exemple, si après je fais ls il ne trouve rien, vu que le chemin a été supprimé.

si je fais echo une variable qui a été suppr', ça n'affiche rien. Enfin un saut à la ligne si j'ai pas fait echo -n.
La plupart du temps y'a pas de messages d'erreur mais si je fais 'unset $PATH' au lieu de 'unset PATH' j'ai un message
d'erreur.
si je fais 'unset $USER' juste ça fait rien...
bizarre la gestion d'erreur mais bon.

si je met plusieurs arguments, ils sont tous exécutés. Même si ils sont tous faux sauf un au milieu ça va marcher.
*/