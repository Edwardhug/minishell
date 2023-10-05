// #include "../../include/minishell.h"

// t_env	*ft_lstcpy(t_env *source)
// {
// 	t_env	*dest;
// 	t_env	*new_node;
// 	t_env	*tail;
// 	t_env	*tmp;

// 	tmp = source;
// 	dest = NULL;
// 	while (tmp)
// 	{
// 		new_node = malloc(sizeof(t_env));
// 		if (!new_node)
// 			return (perror("malloc"), NULL);
// 		new_node->name = ft_strdup(tmp->name);
// 		new_node->value = ft_strdup(tmp->value);
// 		new_node->next = NULL;
// 		if (!dest)
// 		{
// 			dest = new_node;
// 			tail = new_node;
// 		}
// 		else
// 		{
// 			tail->next = new_node;
// 			tail = new_node;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (dest);
// }