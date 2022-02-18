/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_node_exe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:07:42 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:07:45 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_node_exe(t_cmd *cmd)
{
	cmd->exe = malloc(sizeof(t_exe));
	if (!cmd->exe)
		ft_mistake("Error: Out of memory\n", cmd);
	if (cmd->exe)
	{
		cmd->exe->comnd = NULL;
		cmd->exe->infile = NULL;
		cmd->exe->outfile = NULL;
		cmd->exe->append = NULL;
		cmd->exe->limiter = NULL;
		cmd->exe->next = NULL;
		cmd->exe->cmd_arg = NULL;
		cmd->exe->fd1 = dup(STDIN_FILENO);
		cmd->exe->fd2 = dup(STDOUT_FILENO);
		cmd->exe->cmdi_path = NULL;
	}
}
