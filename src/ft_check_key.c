/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:06:01 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:06:03 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_key(t_list *env_list, char *key, char *err, char *object)
{
	int		flag;
	t_list	*tmp;

	flag = 0;
	tmp = env_list;
	while (tmp != NULL)
	{
		if (ft_str_cmp(tmp->key, key) == 0)
			flag = 1;
		tmp = tmp->next;
	}
	if (flag == 0)
		ft_error("minishell: ", object, err, g_error);
	return (flag);
}
