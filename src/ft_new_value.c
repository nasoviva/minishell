/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:08:29 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:08:31 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_new_value(t_list *list, char *key, char *value, t_cmd *cmd)
{
	t_list	*tmp;
	int		out;

	tmp = list;
	out = 0;
	while (tmp && out == 0)
	{
		if (ft_str_cmp(tmp->key, key) == 0)
		{
			ft_free_char(tmp->value);
			if (value)
				tmp->value = ft_strdup(value, cmd);
			else
				tmp->value = NULL;
			out = 1;
		}
		tmp = tmp->next;
	}
}
