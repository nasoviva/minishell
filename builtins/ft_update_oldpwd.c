/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_oldpwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:13:28 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:13:30 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_oldpwd(t_cmd *cmd)
{
	char	*current_dir;
	char	*new_dir;

	new_dir = NULL;
	current_dir = ft_get_some_dir(cmd, "PWD");
	if (current_dir != NULL)
	{
		ft_new_value(cmd->env_list, "OLDPWD", current_dir, cmd);
		ft_new_value(cmd->export_list, "OLDPWD", current_dir, cmd);
		ft_free_char(current_dir);
	}
	else if (current_dir == NULL)
	{
		if (cmd->oldpwd == 0)
			new_dir = NULL;
		else
			new_dir = ft_getcwd(cmd);
		ft_new_value(cmd->env_list, "OLDPWD", new_dir, cmd);
		ft_new_value(cmd->export_list, "OLDPWD", new_dir, cmd);
		ft_free_char(new_dir);
	}
}
