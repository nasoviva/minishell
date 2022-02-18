/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cycle_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:10:33 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:10:34 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_execv_commands(t_cmd *cmd)
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

static void	ft_close_ends(int *end, t_cmd *cmd)
{
	if (close(end[0]) < 0)
		ft_mistake("Can't close end0\n", cmd);
	if (close(end[1]) < 0)
		ft_mistake("Can't close end1\n", cmd);
}

void	ft_cycle_pipes(t_cmd *cmd)
{
	pid_t	process;
	int		end[2];

	if (pipe(end) == -1)
		ft_mistake("Error in pipe - there is no connection.\n", cmd);
	process = fork();
	if (process < 0)
		ft_mistake("Error in fork\n", cmd);
	cmd->proc[cmd->pid] = process;
	cmd->pid++;
	if (process == 0)
	{
		if (dup2(end[1], STDOUT_FILENO) == -1)
			ft_mistake("Error in dup2 with end1\n", cmd);
		ft_close_ends(end, cmd);
		ft_execv_commands(cmd);
		exit(g_error);
	}
	if (dup2(end[0], STDIN_FILENO) == -1)
		ft_mistake("Error in dup2 with end0\n", cmd);
	ft_close_ends(end, cmd);
}
