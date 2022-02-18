/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:11:58 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:12:00 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_multy_pipe(t_cmd *cmd)
{
	t_exe	*tmp1;
	int		pipe;

	tmp1 = cmd->exe;
	while (tmp1)
	{
		tmp1->cmd_arg = ft_split(tmp1->comnd, '@', cmd);
		free(tmp1->comnd);
		tmp1 = tmp1->next;
	}
	tmp1 = NULL;
	pipe = cmd->pipe;
	while (pipe > 0)
	{
		ft_cycle_pipes(cmd);
		pipe--;
		ft_free_cmd(cmd->exe->cmd_arg);
		ft_free_node_data(cmd);
		tmp1 = cmd->exe;
		cmd->exe = cmd->exe->next;
		free(tmp1);
	}
}

static int	ft_execv(int tut, t_cmd *cmd)
{
	pid_t	pr;

	tut = 1;
	signal(SIGINT, handler11);
	signal(SIGQUIT, handler11);
	pr = fork();
	if (pr < 0)
		ft_mistake("Error in fork\n", cmd);
	cmd->proc[cmd->pid] = pr;
	if (pr == 0)
	{
		signal(SIGINT, handler1);
		signal(SIGQUIT, handler1);
		ft_execv_i(cmd);
		exit (g_error);
	}
	return (tut);
}

static int	ft_last_command(int tut, t_cmd *cmd)
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
		tut = ft_execv(tut, cmd);
	dup2(cmd->std_in, STDIN_FILENO);
	dup2(cmd->std_out, STDOUT_FILENO);
	return (tut);
}

static void	ft_last_comand(t_cmd *cmd)
{
	int		i;
	int		tut;

	tut = 0;
	tut = ft_last_command(tut, cmd);
	i = 0;
	while (i <= cmd->pid)
	{
		waitpid(cmd->proc[i], &g_error, 0);
		if (tut == 1)
		{
			if (WEXITSTATUS(g_error) > 0)
				g_error = WEXITSTATUS(g_error);
			else if (WTERMSIG(g_error) == 2)
				g_error = 130;
			else if (WTERMSIG(g_error) == 3)
				g_error = 131;
		}
		i++;
	}
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_multiple_pipe(t_cmd *cmd)
{
	ft_multy_pipe(cmd);
	if (cmd->exe->cmd_arg && *cmd->exe->cmd_arg != NULL)
		ft_last_comand(cmd);
	else
	{
		ft_error("minishell: ", ":command", " not found\n", 127);
		dup2(cmd->std_in, STDIN_FILENO);
		dup2(cmd->std_out, STDOUT_FILENO);
	}
}
