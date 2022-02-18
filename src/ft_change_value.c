/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:05:26 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:05:28 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_chng_value(t_list *list, char *key, char *value, t_cmd *cmd)
{
	t_list	*tmp;
	int		change_flag;

	tmp = list;
	change_flag = 1;
	while (tmp)
	{
		if (ft_str_cmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value, cmd);
			change_flag = 0;
			tmp->flag = 1;
		}
		tmp = tmp->next;
	}
	return (change_flag);
}

static char	*ft_find_value(char **mass, t_cmd *cmd)
{
	int		i;
	char	*value;

	if (mass[1])
	{
		value = ft_strdup(mass[1], cmd);
		i = 2;
		while (mass[i] != NULL)
		{
			value = ft_strjoin(value, mass[i], cmd);
			i++;
		}
	}
	else
		value = NULL;
	return (value);
}

int	ft_change_value(char *comd, t_list *list, t_cmd *cmd)
{
	int		change_flag;
	char	*key;
	char	*value;
	char	**mass;

	mass = NULL;
	if (ft_char_inside_str(comd, '=') == 0)
	{
		mass = ft_split(comd, '=', cmd);
		key = ft_strdup(mass[0], cmd);
		value = ft_find_value(mass, cmd);
		ft_free_cmd(mass);
	}
	else
	{
		key = ft_strdup(comd, cmd);
		value = NULL;
	}
	change_flag = ft_chng_value(list, key, value, cmd);
	free(key);
	ft_free_char(value);
	return (change_flag);
}
