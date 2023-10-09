#include "../../include/minishell.h"

// this c file is for export HELLO="123 A-"

int	ft_isupper(int n)
{
	if (n >= 65 && n <= 90)
		return (1);
	return (0);
}

void fill_var_node(t_struct **list_word, char *word)
{
	t_struct	*tmp;
	t_enum		type;
	char	*str;
	int		i;

	if (!word)
		return ;
	i = 0;
	while (word[i])
	{
		str = get_node(word, &i);
		tmp = *list_word;
		type = find_type_enum(tmp, str);		//currently working on this
		add_node_back(list_word, new_node(str, type));
	}
	free(word);
}

int	get_len_var(char *line, int *i, t_struct **list_word)
{
	int	j;
	int	quotes;			// will help us to check for = and for "
	int equal;
	int copy;

	j = 0;
	quotes = 0;
	equal = 0;
	copy = (*i);
	while (line[copy] && (quotes + equal) < 3)
	{
		if (line[copy] == '=')
			equal++;
		else if (line[copy] == '\"')
			quotes++;
		else if (line[copy] == ' ' && quotes < 1)
			return (j);
		j++;
		copy++;
	}
	if ((quotes + equal) < 3)
		return (fill_node(list_word, find_end_of_the_word(line, i)), 0);
	return (j);
}

char	*find_end_var(char *line, int *i, t_struct **list_word)
{
	int		len;
	char	*word;
	int		j;

	len = get_len_var(line, i, list_word);
	if (len == 0)
		return (NULL);
	word = calloc((len + 1), sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
	{
		word[j] = line[(*i) + j];
		j++;
	}
	(*i) = (*i) + j;
	return (word);
}