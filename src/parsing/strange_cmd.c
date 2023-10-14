#include "../../include/minishell.h"

int	impair_quote(char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			s_quote++;
		if (str[i] == '\"')
			d_quote++;
		i++;
	}
	if (d_quote % 2 != 0)
		return (1);
	if (s_quote % 2 != 0)
		return (2);
	return (0);
}

int	have_strange_cmd(char *str)
{
	if (str[0] == '|')
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), g_error_value = 2 * 256, 1);
	if (impair_quote(str) == 1)
		return (ft_putstr_fd("syntax error near unexpected token \"\n", 2), g_error_value = 2 * 256, 1);
	if (impair_quote(str) == 2)
		return (ft_putstr_fd("syntax error near unexpected token \'\n", 2), g_error_value = 2 * 256, 1);
	return (0);
}
