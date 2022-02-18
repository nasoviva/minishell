/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:12:51 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:12:53 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_echo_bla_bla(t_cmd *cmd)
{
	int	i;

	i = 0;
	i++;
	while (cmd->exe->cmd_arg[i] != NULL && cmd->exe->cmd_arg[i + 1] != NULL)
	{
		ft_putstr(cmd->exe->cmd_arg[i]);
		write(1, " ", 1);
		i++;
	}
	if (cmd->exe->cmd_arg[i])
		ft_putstr(cmd->exe->cmd_arg[i]);
	write(1, "\n", 1);
	g_error = 0;
}

static void	ft_echo_n(t_cmd *cmd)
{
	int	i;

	i = 0;
	i++;
	while (cmd->exe->cmd_arg[i + 1] != NULL && cmd->exe->cmd_arg[i + 2] != NULL)
	{
		ft_putstr(cmd->exe->cmd_arg[i + 1]);
		write(1, " ", 1);
		i++;
	}
	if (cmd->exe->cmd_arg[i + 1])
		ft_putstr(cmd->exe->cmd_arg[i + 1]);
	g_error = 0;
}

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (ft_str_cmp(cmd->exe->cmd_arg[i], "echo") == 0 \
	&& cmd->exe->cmd_arg[i + 1] == NULL)
	{
		write(1, "\n", 1);
		g_error = 0;
	}
	else if (ft_str_cmp(cmd->exe->cmd_arg[i], "echo") == 0 && \
	ft_str_cmp(cmd->exe->cmd_arg[i + 1], "-n") != 0)
		ft_echo_bla_bla(cmd);
	else if (ft_str_cmp(cmd->exe->cmd_arg[i], "echo") == 0 && \
	ft_str_cmp(cmd->exe->cmd_arg[i + 1], "-n") == 0)
		ft_echo_n(cmd);
}
