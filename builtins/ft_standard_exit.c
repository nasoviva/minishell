/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_standard_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:13:17 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:13:19 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_close(t_cmd *cmd)
{
	ft_free(cmd);
	if (cmd->env_list != NULL)
		ft_free_list(cmd->env_list);
	if (cmd->export_list != NULL)
		ft_free_list(cmd->export_list);
	if (close(cmd->std_in) < 0)
		ft_mistake("Can't close\n", cmd);
	if (close(cmd->std_out) < 0)
		ft_mistake("Can't close\n", cmd);
	clear_history();
	exit(0);
}

static void	ft_layer2_with_args(t_cmd *cmd)
{
	if (ft_isdigit(cmd->exe->cmd_arg[1]) == 0 && *cmd->exe->cmd_arg[1] != '\0')
	{
		if (cmd->exe->cmd_arg[2] != NULL)
		{
			g_error = 1;
			write(2, "exit\nminishell: exit: too many arguments\n",
				  ft_strlen("exit\nminishell: exit: too many arguments\n"));
		}
		else
		{
			g_error = ft_atoi(cmd->exe->cmd_arg[1]);
			printf("exit\n");
			ft_close(cmd);
		}
	}
	else
	{
		ft_error("exit\nminishell: exit: ", cmd->exe->cmd_arg[1], \
				": numeric argument required\n", 255);
		ft_close(cmd);
	}
}

void	ft_standard_exit(t_cmd *cmd)
{
	if (cmd->exe->cmd_arg[1] != NULL)
		ft_layer2_with_args(cmd);
	else
	{
		g_error = 0;
		write(1, "exit\n", 5);
		ft_close(cmd);
	}
}
