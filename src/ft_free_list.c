/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:06:52 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:06:54 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_list(t_list *list)
{
	t_list	*tmp;
	t_list	*dell;

	tmp = NULL;
	tmp = list;
	while (tmp)
	{
		dell = tmp;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		tmp = tmp->next;
		free(dell);
	}
}
