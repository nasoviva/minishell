/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:13:09 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:13:11 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*ft_print_rest(t_list *tmp)
{
	ft_putstr("declare -x ");
	ft_putstr(tmp->key);
	if (tmp->flag == 1 && tmp->value == NULL)
	{
		write(1, "=\"", 2);
		write(1, "\"", 1);
	}
	else if (tmp->value)
	{
		write(1, "=\"", 2);
		ft_putstr(tmp->value);
		write(1, "\"", 1);
	}
	return (tmp);
}

static void	ft_print_export(t_cmd *cmd)
{
	t_list	*tmp;

	if (cmd->exe->cmd_arg[1] == NULL)
	{
		tmp = cmd->export_list;
		while (tmp != NULL)
		{
			if (ft_str_cmp(tmp->key, "OLDPWD") == 0 && cmd->oldpwd == 0)
			{
				ft_putstr("declare -x ");
				ft_putstr(tmp->key);
				write(1, "\n", 1);
				tmp = tmp->next;
			}
			else
			{
				tmp = ft_print_rest(tmp);
				write(1, "\n", 1);
				tmp = tmp->next;
			}
		}
	}
}

static int	ft_ch_val(t_cmd *cmd, int t)
{
	if (ft_change_value(cmd->exe->cmd_arg[t], cmd->export_list, cmd)
		== 1)
		cmd->export_list = ft_add_node_back(cmd->export_list, \
				cmd->exe->cmd_arg[t], cmd);
	if (ft_char_inside_str(cmd->exe->cmd_arg[t], '=') == 0)
	{
		if (ft_change_value(cmd->exe->cmd_arg[t], cmd->env_list, cmd)
			== 1)
			cmd->env_list = ft_add_node_back(cmd->env_list, \
					cmd->exe->cmd_arg[t], cmd);
	}
	return (t);
}

static void	ft_add_or_change_value(t_cmd *cmd)
{
	int	t;

	if (cmd->exe->cmd_arg[1] != NULL)
	{
		t = 1;
		while (cmd->exe->cmd_arg[t])
		{
			if (ft_isalpha(*cmd->exe->cmd_arg[t]) == 1)
			{
				ft_error("export: '", cmd->exe->cmd_arg[t], \
				"': not a valid identifier or wrong syntax\n", 1);
				break ;
			}
			else
				t = ft_ch_val(cmd, t);
			t++;
		}
	}
}

void	ft_export(t_cmd *cmd)
{
	ft_print_export(cmd);
	if (cmd->pipe == 0)
		ft_add_or_change_value(cmd);
}
