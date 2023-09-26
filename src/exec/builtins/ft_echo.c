#include "../../../include/minishell.h"

int	ft_echo(char **cmd)
{
	int	dash_n; //sert de booléen
	int	i;

	i = 1;
	if (ft_strnstr(cmd[1], "-n", 2) != NULL) //on regarde si on a le -n pour le saut à la ligne
	{
		i++;
		dash_n = 0;
	}
	else
		dash_n = 1;
	while (cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL) //si on est pas au dernier argument, on met un espace.
			ft_printf(" ");
		i++;
	}
	if (dash_n) //si on a pas de -n on va à la ligne
		ft_printf("\n");
	return (0);
}