#include "../../include/minishell.h"

// int	impair_quote(char *str)
// {
// 	int	i;
// 	int	s_quote;
// 	int	d_quote;

// 	i = 0;
// 	s_quote = 0;
// 	d_quote = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 			s_quote++;
// 		if (str[i] == '\"')
// 			d_quote++;
// 		i++;
// 	}
// 	if (d_quote % 2 != 0)
// 		return (1);
// 	if (s_quote % 2 != 0)
// 		return (2);
// 	return (0);
// }

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
