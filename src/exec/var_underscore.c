#include "../../include/minishell.h"

void	change_underscore(char *cmd, t_exec *exec)
{
	t_env	*tmp_env;
	t_env	*tmp_exp;

	tmp_env = exec->env;
	tmp_exp = exec->export;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->name, "_") == 0)
		{
			while (tmp_exp)
			{
				if (ft_strcmp(tmp_exp->name, "_") == 0)
					break ;
				tmp_exp = tmp_exp->next;
			}
			if (tmp_env->value[0])
			{
				free(tmp_env->value);
			}
			tmp_env->value = ft_strdup(cmd);
			if (!tmp_env->value)
			{
				free(cmd);
				free_exec_struct(exec);
				exit(EXIT_FAILURE);
			}
			if (tmp_exp->value[0])
				free(tmp_exp->value);
			tmp_exp->value = ft_strdup(cmd);
			if (!tmp_exp->value)
			{
				free(cmd);
				free_exec_struct(exec);
				exit(EXIT_FAILURE);
			}
			return ;
		}
		tmp_env = tmp_env->next;
	}
}