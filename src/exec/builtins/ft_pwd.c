#include "../../../include/minishell.h"

int	ft_pwd(t_exec *exec)
{
	char	*cwd;
	
	cwd = malloc(sizeof(char *) * (PATH_MAX + 1)); //prend la taille max d'un path en malloc
	if (getcwd(cwd, PATH_MAX) != NULL) //stock le path dans cwd 
	{
		ft_printf("%s\n", cwd);
		free(cwd);
	}
	else
	{
		perror("Path error");
		free(cwd);
		g_error_value = -127;
		return (1);
	}
	if (exec->nb_cmds > 1)
	{
		free_exec_fork(exec);
		exit(0);
	}
	return (0);
}
