/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:12:43 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:12:45 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_path_check(t_cmd *cmd)
{
	char	**tmp;
	int		result;

	result = 0;
	tmp = cmd->mypathes;
	while (*tmp)
	{
		if (ft_str_cmp(*tmp, "/usr/bin") == 0)
			result = 1;
		tmp++;
	}
	return (result);
}

static void	ft_print_env(t_cmd *cmd)
{
	t_list	*tmp;

	tmp = cmd->env_list;
	while (tmp != NULL)
	{
		if (ft_str_cmp(tmp->key, "OLDPWD") == 0 && cmd->oldpwd == 0)
			tmp = tmp->next;
		else
		{
			ft_putstr(tmp->key);
			if (tmp->flag == 1)
				write(1, "=", 1);
			if (tmp->value)
				ft_putstr(tmp->value);
			write(1, "\n", 1);
			tmp = tmp->next;
		}
	}
}

void	ft_env(t_cmd *cmd)
{
	if (cmd->exe->cmd_arg[0] && cmd->exe->cmd_arg[1] != NULL)
		ft_error("env: ", cmd->exe->cmd_arg[1], \
		": No such file or directory\n", 127);
	else if (cmd->exe->cmd_arg[0] && cmd->exe->cmd_arg[1] == NULL)
	{
		if (ft_check_key(cmd->env_list, "PATH", \
		": No such file or directory\n", "env") != 0)
		{
			if (ft_env_path_check(cmd) == 0)
			{
				g_error = 127;
				write(2, "minishell: env: command not found\n", \
				ft_strlen("minishell: env: command not found\n"));
			}
			else
				ft_print_env(cmd);
		}
		else
			g_error = 127;
	}
}
