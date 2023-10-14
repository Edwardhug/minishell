#include "../../include/minishell.h"

int	last_char_redir(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i + 1])
		i++;
	if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (1);
	return (0);
}

int	have_strange_cmd(char *str)
{
	if (str[0] == '|')
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), g_error_value = 2 * 256, 1);
	if (last_char_redir(str))
		return (ft_putstr_fd("syntax error near unexpected token `newline'\n", 2), g_error_value = 2 * 256, 1);
	return (0);
}
