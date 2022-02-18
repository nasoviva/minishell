/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_list_creation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:06:34 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:06:41 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_export_list_creation(char **envp, t_cmd *cmd)
{
	char	**my_envp;
	t_list	*export_list;

	export_list = NULL;
	my_envp = envp;
	export_list = ft_init_node(export_list, *my_envp, cmd);
	my_envp++;
	while (*my_envp != NULL)
	{
		export_list = ft_add_node_back(export_list, *my_envp, cmd);
		my_envp++;
	}
	return (export_list);
}
