/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:04:08 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:04:10 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*ft_value(t_list *new, t_cmd *cmd, char **mass)
{
	int		i;

	new->value = ft_strdup(mass[1], cmd);
	i = 2;
	while (mass[i] != NULL)
	{
		new->value = ft_strjoin(new->value, mass[i], cmd);
		i++;
	}
	return (new);
}

static t_list	*ft_node(t_list *new, t_cmd *cmd, char *comd)
{
	char	**mass;

	mass = NULL;
	if (ft_char_inside_str(comd, '=') == 0)
	{
		new->flag = 1;
		mass = ft_split(comd, '=', cmd);
		new->key = ft_strdup(mass[0], cmd);
		if (mass[1])
			new = ft_value(new, cmd, mass);
		else
			new->value = NULL;
		ft_free_cmd(mass);
	}
	else
	{
		new->flag = 0;
		new->key = ft_strdup(comd, cmd);
		new->value = NULL;
	}
	new->next = NULL;
	return (new);
}

t_list	*ft_add_node_back(t_list *list, char *comd, t_cmd *cmd)
{
	t_list		*tmp;
	t_list		*new;

	tmp = NULL;
	tmp = list;
	while (list->next != NULL)
		list = list->next;
	new = malloc(sizeof(t_list));
	if (!new)
		ft_mistake("Error: Out of memory\n", cmd);
	if (new)
		new = ft_node(new, cmd, comd);
	list->next = new;
	list = tmp;
	return (list);
}
