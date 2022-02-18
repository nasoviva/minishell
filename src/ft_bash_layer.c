/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bash_layer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:05:08 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:05:11 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_minish_pipe(t_cmd *cmd)
{
	char	*value;
	int		layer;
	int		i;

	i = 0;
	if (cmd->exe->cmd_arg[i] && cmd->exe->cmd_arg[i + 1] == NULL)
	{
		value = ft_get_some_dir(cmd, "SHLVL");
		layer = ft_atoi(value);
		free(value);
		layer++;
		value = ft_itoa(layer, cmd);
		ft_new_value(cmd->env_list, "SHLVL", value, cmd);
		ft_new_value(cmd->export_list, "SHLVL", value, cmd);
		free(value);
		g_error = 0;
	}
	else if (cmd->exe->cmd_arg[i] && cmd->exe->cmd_arg[i + 1] != NULL)
	{
		ft_error("minishell: ", cmd->exe->cmd_arg[i + 1], \
		": No such file or directory\n", 127);
	}
}

static void	ft_execv(t_cmd *cmd)
{
	pid_t	pr;

	pr = fork();
	if (pr == 0)
	{
		ft_execv_i(cmd);
		exit (g_error);
	}
	waitpid(pr, &g_error, 0);
	if (WEXITSTATUS(g_error) > 0)
		g_error = WEXITSTATUS(g_error);
	else if (WTERMSIG(g_error) == 2)
		g_error = 130;
	else if (WTERMSIG(g_error) == 3)
		g_error = 131;
}

static void	ft_command(t_cmd *cmd)
{
	if (ft_str_cmp(cmd->exe->cmd_arg[0], "minishell") == 0)
		ft_minish_pipe(cmd);
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
		ft_execv(cmd);
}

static void	ft_minishell_with_pipe(t_cmd *cmd)
{
	char	*input;

	while (1)
	{
		input = NULL;
		input = readline("minishell$ ");
		if (input == NULL)
		{
			write(1, "\033[A\n", ft_strlen("\033[A\n"));
			rl_redisplay();
			break ;
		}
		else
		{
			free(cmd->exe->cmd_arg[0]);
			cmd->exe->cmd_arg[0] = ft_strdup(input, cmd);
			ft_command(cmd);
		}
		free(input);
	}
}

void	ft_bash_layer(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd->pipe == 0 && cmd->exe->cmd_arg[i] \
	&& cmd->exe->cmd_arg[i + 1] == NULL)
		ft_up(cmd);
	else if (cmd->exe->cmd_arg[i] && cmd->exe->cmd_arg[i + 1] != NULL)
	{
		ft_error("minishell: ", cmd->exe->cmd_arg[i + 1], \
		": No such file or directory\n", 127);
	}
	else if (cmd->pipe != 0 && cmd->exe->cmd_arg[i] \
	&& cmd->exe->cmd_arg[i + 1] == NULL)
		ft_minishell_with_pipe(cmd);
}
