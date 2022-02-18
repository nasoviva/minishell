/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execv_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:11:05 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:11:07 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_no_cmd(t_cmd *cmd)
{
	int		y;
	char	*tmp;

	y = ft_strlen(cmd->exe->cmd_arg[0]);
	if ((*cmd->exe->cmd_arg[0] == '\'' && cmd->exe->cmd_arg[0][y - 1] == '\'') \
	|| (*cmd->exe->cmd_arg[0] == '\"' && cmd->exe->cmd_arg[0][y - 1] == '\"'))
	{
		tmp = cmd->exe->cmd_arg[0];
		cmd->exe->cmd_arg[0] = ft_substr(cmd->exe->cmd_arg[0], 1, y - 2, cmd);
		free(tmp);
	}
	if (ft_char_inside_str(cmd->exe->cmd_arg[0], '/') == 0)
		ft_error("minishell: ", cmd->exe->cmd_arg[0], \
		" : No such file or directory\n", 127);
	else
		ft_error("minishell: ", cmd->exe->cmd_arg[0], \
		": command not found\n", 127);
}

void	ft_execv_i(t_cmd *cmd)
{
	if (cmd->path == NULL)
		ft_error("minishell: ", cmd->exe->cmd_arg[0], \
		" : No such file or directory\n", 127);
	else
	{
		cmd->exe->cmdi_path = ft_path(cmd->exe->cmd_arg[0], cmd->mypathes, cmd);
		if (cmd->exe->cmdi_path == NULL)
			ft_no_cmd(cmd);
		else
		{
			ft_copy_from_list(cmd->env_list, cmd);
			if (execve(cmd->exe->cmdi_path, cmd->exe->cmd_arg, cmd->envp) == -1)
			{
				if (ft_char_inside_str(cmd->exe->cmd_arg[0], '/') == 0)
					ft_error("minishell: ", cmd->exe->cmd_arg[0], \
				": is a directory\n", 126);
				else
					ft_error("minishell: ", cmd->exe->cmd_arg[0], \
				": command not found\n", 127);
			}
		}
	}
}
