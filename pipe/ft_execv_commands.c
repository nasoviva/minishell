/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execv_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:10:55 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:10:57 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execv_commands(t_cmd *cmd)
{
	if (ft_str_cmp(cmd->exe->cmd_arg[0], "minishell") == 0)
		ft_bash_layer(cmd);
	else if (ft_str_cmp(cmd->exe->cmd_arg[0], "env") == 0)
		ft_env(cmd);
	else if (ft_str_cmp(cmd->exe->cmd_arg[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_str_cmp(cmd->exe->cmd_arg[0], "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_str_cmp(cmd->exe->cmd_arg[0], "unset") == 0)
		ft_unset(cmd);
	else if (ft_str_cmp(cmd->exe->cmd_arg[0], "export") == 0)
		ft_export(cmd);
	else if (ft_str_cmp(cmd->exe->cmd_arg[0], "cd") == 0)
		ft_cd(cmd);
	else if (ft_str_cmp(cmd->exe->cmd_arg[0], "exit") == 0)
		ft_exit(cmd);
	else
		ft_execv_i(cmd);
}
