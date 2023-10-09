#include "../../include/minishell.h"

int	ft_error_message_arg(char *cmd_name, char *arg, char *msg)
{
	char	*error_message;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_strjoin("minishell: ", cmd_name);
	if (!tmp1)
		return (perror("error_message tmp join error"), 1);
	tmp2 = ft_strjoin(tmp1, ": ");
	if (!tmp2)
		return (perror("error_message tmp2 join error"), 1);
	free(tmp1);
	tmp3 = ft_strjoin(tmp2, arg);
	if (!tmp3)
		return (perror("error_message tmp3 join error"), 1);
	free(tmp2);
	error_message = ft_strjoin(tmp3, msg);
	if (!error_message)
		return (perror("error_message join error"), 1);
	free(tmp3);
	ft_putstr_fd(error_message, 2);
	free(error_message);
	return (0);
}

int	ft_error_message(char *cmd_name, char *msg)
{
	char	*error_message;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", cmd_name);
	if (!tmp)
		return (perror("error_message tmp join error"), 1);
	error_message = ft_strjoin(tmp, msg);
	if (!error_message)
		return (perror("error_message join error"), 1);
	free(tmp);
	ft_putstr_fd(error_message, 2);
	free(error_message);
	return (0);
}