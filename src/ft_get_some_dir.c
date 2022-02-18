/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_some_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:07:13 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:07:15 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_some_dir(t_cmd *cmd, char *key)
{
	t_list	*tmp;
	int		out;
	char	*new_dir;

	new_dir = NULL;
	tmp = cmd->env_list;
	out = 0;
	while (tmp && out == 0)
	{
		if (ft_str_cmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				new_dir = ft_strdup(tmp->value, cmd);
			else
				new_dir = NULL;
			out = 1;
		}
		tmp = tmp->next;
	}
	return (new_dir);
}
