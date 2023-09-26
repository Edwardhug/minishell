#include "../../../include/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;
	
	
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
	}
	else
		ft_printf("%s\n", cwd);
	return (0);
}