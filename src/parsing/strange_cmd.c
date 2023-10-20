#include "../../include/minishell.h"

int	end_of_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	last_char_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '>' || str[i] == '<' || str[i] == '|')
			&& end_of_str(str + i + 1))
			return (1);
		i++;
	}
	return (0);
}

int	have_strange_cmd(char *str)
{
	if (str[0] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (g_error_value = 2 * 256, 1);
	}
	if (last_char_redir(str))
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (g_error_value = 2 * 256, 1);
	}
	return (0);
}
