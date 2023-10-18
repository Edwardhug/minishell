#include "../../include/minishell.h"

void    shlvl(t_exec *exec, int empty_env, int more_or_less)
{
    t_env    *tmp_env;
    t_env    *tmp_exp;
    int        int_shlvl;

    if (empty_env == 1)
    {
        exec->env = ft_lstnew_env("SHLVL=1", 5);
        exec->export = ft_lstnew_env("SHLVL=1", 5);
        return ;
    }
    tmp_env = exec->env;
    tmp_exp = exec->export;
    while (tmp_env)
    {
        if (ft_strcmp(tmp_env->name, "SHLVL") == 0)
        {
            while (tmp_exp)
            {
                if (ft_strcmp(tmp_exp->name, "SHLVL") == 0)
                    break ;
                tmp_exp = tmp_exp->next;
            }
            int_shlvl = ft_atoi(tmp_env->value);
            if (more_or_less == 1)
            {
                int_shlvl++;
                if (int_shlvl > 1000)
                    int_shlvl = 0;
            }
            else
                int_shlvl--;
            free(tmp_env->value);
            free(tmp_exp->value);
            tmp_env->value = ft_itoa(int_shlvl);
            if (!tmp_env->value)
            {
                free_exec_struct(exec);
                exit(EXIT_FAILURE);
            }
            tmp_exp->value = ft_itoa(int_shlvl);
            if (!tmp_exp->value)
            {
                free_exec_struct(exec);
                exit(EXIT_FAILURE);
            }
            break ;
        }
        tmp_env = tmp_env->next;
    }
}

void    change_underscore(char *cmd, t_exec *exec)
{
    t_env    *tmp_env;
    t_env    *tmp_exp;

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
            if (tmp_env->value[0] && !(ft_strcmp(cmd, "echo") == 0))
            {
                free(tmp_env->value);
            }
            if (!(ft_strcmp(cmd, "echo") == 0))
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