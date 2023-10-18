#include "../../include/minishell.h"

char	*fill_str(char *word, int *i, int size)
{
	char	*str;
	int		j;

	str = ft_calloc((size + 1), sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (j < size)
	{
		str[j] = word[(*i) - size + j];
		j++;
	}
	return (str);
}

char	*get_node(char *word, int *i)
{
	int	size;

	size = 0;
	if (word[*i] && (word[*i] == '|' || word[*i] == '<' || word[*i] == '>'))
	{
		while (word[*i] && (word[*i] == '|'
				|| word[*i] == '<' || word[*i] == '>'))
		{
			size++;
			(*i)++;
		}
	}
	else if (word[*i] && (word[*i] != '|'
			&& word[*i] != '<' && word[*i] != '>'))
	{
		while (word[*i] && (word[*i] != '|'
				&& word[*i] != '<' && word[*i] != '>'))
		{
			size++;
			(*i)++;
		}
	}
	return (fill_str(word, i, size));
}
