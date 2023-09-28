#include "../../../include/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;
	
	cwd = malloc(sizeof(char *) * (PATH_MAX + 1)); //prend la taille max d'un path en malloc
	if (getcwd(cwd, PATH_MAX) != NULL) //stock le path dans cwd
	{
		ft_printf("%s\n", cwd); //affiche cwd
		free(cwd);
		exit(0);
	}
	else
	{
		perror("getcwd");
		free(cwd);
		exit(1);
	}
}