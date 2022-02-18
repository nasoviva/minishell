/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_from_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgummy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:23:53 by sgummy            #+#    #+#             */
/*   Updated: 2021/12/23 17:24:02 by sgummy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_env_len(t_list *env_list)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = env_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_copy_from_list(t_list *env_list, t_cmd *cmd)
{
	int		i;
	int		j;
	t_list	*tmp;

	i = ft_env_len(env_list);
	cmd->envp = (char **) malloc(sizeof (char *) * (i + 1));
	if (!cmd->envp)
		ft_mistake("Error: Out of memory\n", cmd);
	j = 0;
	tmp = env_list;
	while (j < i)
	{
		cmd->envp[j] = ft_strjoin(tmp->key, tmp->value, cmd);
		j++;
		tmp = tmp->next;
	}
	cmd->envp[j] = NULL;
}
