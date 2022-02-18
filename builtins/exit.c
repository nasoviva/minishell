/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:13:01 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:13:02 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_down_layer(t_cmd *cmd, int layer)
{
	char	*value;

	layer--;
	value = ft_itoa(layer, cmd);
	ft_new_value(cmd->env_list, "SHLVL", value, cmd);
	ft_new_value(cmd->export_list, "SHLVL", value, cmd);
	free(value);
}

static void	ft_layer_over2_with_args(t_cmd *cmd, int layer)
{
	if (ft_isdigit(cmd->exe->cmd_arg[1]) == 0 && *cmd->exe->cmd_arg[1] != '\0')
	{
		if (cmd->exe->cmd_arg[2] != NULL)
		{
			g_error = 1;
			write(2, "exit\nminishell: exit: too many arguments\n", \
			ft_strlen("exit\nminishell: exit: too many arguments\n"));
		}
		else
		{
			g_error = ft_atoi(cmd->exe->cmd_arg[1]);
			printf("exit\n");
			ft_down_layer(cmd, layer);
		}
	}
	else
	{
		ft_error("exit\nminishell: exit: ", cmd->exe->cmd_arg[1], \
		": numeric argument required\n", 255);
		ft_down_layer(cmd, layer);
	}
}

void	ft_exit(t_cmd *cmd)
{
	char	*value;
	int		layer;

	value = ft_get_some_dir(cmd, "SHLVL");
	layer = ft_atoi(value);
	free(value);
	if (layer == 2 && cmd->pipe == 0)
		ft_standard_exit(cmd);
	else if (layer > 2 && cmd->pipe == 0)
	{
		if (cmd->exe->cmd_arg[1] != NULL)
			ft_layer_over2_with_args(cmd, layer);
		else
		{
			g_error = 0;
			write(1, "exit\n", 5);
			ft_down_layer(cmd, layer);
		}
	}
}
