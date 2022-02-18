/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:06:23 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:06:25 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_env_list_creation(char **envp, t_cmd *cmd)
{
	char	**my_envp;
	t_list	*env_list;

	env_list = NULL;
	my_envp = envp;
	env_list = ft_init_node(env_list, *my_envp, cmd);
	my_envp++;
	while (*my_envp != NULL)
	{
		env_list = ft_add_node_back(env_list, *my_envp, cmd);
		my_envp++;
	}
	return (env_list);
}
