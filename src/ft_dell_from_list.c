/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dell_from_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:06:13 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:06:15 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*ft_first_node(t_list **list, t_list	*tmp)
{
	*list = (*list)->next;
	free(tmp->key);
	tmp->key = NULL;
	free(tmp->value);
	tmp->value = NULL;
	tmp->next = NULL;
	free(tmp);
	tmp = NULL;
	return (tmp);
}

static t_list	*ft_some_node(t_list	*tmp, t_list *tmp0, t_list *tmp2)
{
	while (tmp0->next != tmp)
		tmp0 = tmp0->next;
	tmp0->next = tmp2;
	free(tmp->key);
	free(tmp->value);
	tmp->next = NULL;
	free(tmp);
	tmp = tmp0;
	return (tmp);
}

static t_list	*ft_dell(t_list *tmp, t_list *tmp0, t_list **list)
{
	t_list	*tmp2;

	tmp2 = tmp->next;
	if (tmp != tmp0)
		tmp = ft_some_node(tmp, tmp0, tmp2);
	else if (tmp == *list)
		tmp = ft_first_node(list, tmp);
	return (tmp);
}

void	ft_del_from_list(char **argv, t_list **list)
{
	t_list	*tmp;
	t_list	*tmp0;
	int		i;

	tmp = *list;
	tmp0 = *list;
	while (tmp != NULL)
	{
		i = 1;
		while (argv[i])
		{
			if (ft_str_cmp(tmp->key, argv[i]) == 0)
				tmp = ft_dell(tmp, tmp0, list);
			i++;
		}
		if (tmp)
			tmp = tmp->next;
	}
}
