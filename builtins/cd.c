/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:12:34 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:12:36 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_new_dir(char *dir, t_cmd *cmd)
{
	char	*buf;
	int		len;
	char	*new_dir;
	char	*result;

	new_dir = NULL;
	len = 100500;
	buf = malloc(sizeof (char) * len);
	if (!buf)
		ft_mistake("Error: Out of memory\n", cmd);
	if (chdir(dir) == -1)
	{
		ft_error("minishell: cd: ", dir, ": No such file or directory\n", 1);
		ft_free_char(buf);
		return (new_dir);
	}
	result = getcwd(buf, len);
	new_dir = ft_strdup(result, cmd);
	ft_free_char(buf);
	return (new_dir);
}

static void	ft_back_dir(t_cmd *cmd)
{
	char	*new_dir;
	char	*tmp;

	tmp = ft_get_some_dir(cmd, "OLDPWD");
	new_dir = ft_get_new_dir(tmp, cmd);
	write(1, new_dir, ft_strlen(new_dir));
	write(1, "\n", 1);
	ft_new_value(cmd->env_list, "PWD", new_dir, cmd);
	ft_new_value(cmd->export_list, "PWD", new_dir, cmd);
	ft_free_char(new_dir);
	ft_free_char(tmp);
}

static void	ft_home(t_cmd *cmd, char *new_dir)
{
	char	*tmp;

	if (ft_check_key(cmd->env_list, "HOME", ": HOME not set\n", "cd")
		!= 0 && cmd->pipe == 0)
	{
		ft_update_oldpwd(cmd);
		tmp = ft_get_some_dir(cmd, "HOME");
		new_dir = ft_get_new_dir(tmp, cmd);
		ft_new_value(cmd->env_list, "PWD", new_dir, cmd);
		ft_new_value(cmd->export_list, "PWD", new_dir, cmd);
		free(new_dir);
		ft_free_char(tmp);
		cmd->oldpwd = 1;
	}
	else
		g_error = 1;
}

static void	ft_back_direction(t_cmd *cmd)
{
	char	*new_dir;

	new_dir = NULL;
	new_dir = ft_get_some_dir(cmd, "OLDPWD");
	if (cmd->oldpwd == 0 || new_dir == NULL)
		ft_error("minishell: ", "cd", ": OLDPWD not set\n", 1);
	else
	{
		ft_free_char(new_dir);
		new_dir = ft_get_some_dir(cmd, "PWD");
		if (new_dir == NULL)
			new_dir = ft_getcwd(cmd);
		ft_back_dir(cmd);
		ft_new_value(cmd->env_list, "OLDPWD", new_dir, cmd);
		ft_new_value(cmd->export_list, "OLDPWD", new_dir, cmd);
		ft_free_char(new_dir);
		cmd->oldpwd = 1;
	}
}

void	ft_cd(t_cmd *cmd)
{
	char	*new_dir;

	new_dir = NULL;
	if (cmd->exe->cmd_arg[1] == NULL)
		ft_home(cmd, new_dir);
	else if (cmd->exe->cmd_arg[1] != NULL && *cmd->exe->cmd_arg[1] != '\0')
	{
		if (ft_str_cmp(cmd->exe->cmd_arg[1], "-") == 0)
			ft_back_direction(cmd);
		else
		{
			ft_update_oldpwd(cmd);
			new_dir = ft_get_new_dir(cmd->exe->cmd_arg[1], cmd);
			if (new_dir)
			{
				ft_new_value(cmd->env_list, "PWD", new_dir, cmd);
				ft_new_value(cmd->export_list, "PWD", new_dir, cmd);
				free(new_dir);
				cmd->oldpwd = 1;
			}
		}
	}
}
