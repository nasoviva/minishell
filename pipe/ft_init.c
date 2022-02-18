/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:11:40 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:11:42 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init(t_cmd *cmd, char **envp)
{
	cmd->env_list = ft_env_list_creation(envp, cmd);
	cmd->export_list = ft_export_list_creation(envp, cmd);
	cmd->oldpwd = 0;
	cmd->std_in = dup(STDIN_FILENO);
	cmd->std_out = dup(STDOUT_FILENO);
	if (cmd->std_out == -1 || cmd->std_in == -1)
		ft_mistake("Error in dup\n", cmd);
}

void	ft_init_cmd(t_cmd *cmd)
{
	cmd->path = NULL;
	cmd->mypathes = NULL;
	cmd->quote = 0;
	cmd->f = 0;
	cmd->quote_2 = 0;
	cmd->len = 0;
	cmd->k = 0;
	cmd->argv = NULL;
	cmd->ok = 0;
	cmd->i = 0;
	cmd->pipe = 0;
	cmd->proc = (int *)malloc(sizeof (int) * (cmd->pipe + 100) * 2);
	if (!cmd->proc)
		ft_mistake("Error: Out of memory\n", cmd);
	cmd->pid = 0;
	cmd->exe = NULL;
	cmd->path = ft_get_some_dir(cmd, "PATH");
	if (cmd->path != NULL)
		cmd->mypathes = ft_split(cmd->path, ':', cmd);
	cmd->envp = NULL;
}
