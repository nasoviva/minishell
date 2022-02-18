/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:07:36 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:07:38 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*ft_value(t_list *list, char	**mass, t_cmd *cmd)
{
	int	i;

	if (mass[1])
	{
		list->value = ft_strdup(mass[1], cmd);
		i = 2;
		while (mass[i] != NULL)
		{
			list->value = ft_strjoin(list->value, mass[i], cmd);
			i++;
		}
	}
	else
		list->value = NULL;
	return (list);
}

t_list	*ft_init_node(t_list *list, char *comd, t_cmd *cmd)
{
	char	**mass;

	mass = NULL;
	list = malloc(sizeof(t_list));
	if (!list)
		ft_mistake("Error: Out of memory\n", cmd);
	if (list)
	{
		if (ft_char_inside_str(comd, '=') == 0)
		{
			list->flag = 1;
			mass = ft_split(comd, '=', cmd);
			list->key = ft_strdup(mass[0], cmd);
			list = ft_value(list, mass, cmd);
			ft_free_cmd(mass);
		}
		else
		{
			list->flag = 0;
			list->key = ft_strdup(comd, cmd);
			list->value = NULL;
		}
		list->next = NULL;
	}
	return (list);
}
