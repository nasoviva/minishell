/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:13:41 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:13:43 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_cmd *cmd)
{
	if (cmd->exe->cmd_arg[1] && cmd->pipe == 0)
	{
		if (ft_isalpha(*cmd->exe->cmd_arg[1]) == 1)
			ft_error("minishell: unset: ", cmd->exe->cmd_arg[1], \
			": not a valid identifier\n", 1);
		else
		{
			ft_del_from_list(cmd->exe->cmd_arg, &cmd->env_list);
			ft_del_from_list(cmd->exe->cmd_arg, &cmd->export_list);
			g_error = 0;
		}
	}
}
