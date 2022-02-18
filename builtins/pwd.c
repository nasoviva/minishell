/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:13:35 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:13:37 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	*pwd_dir;
	char	*new_dir;

	pwd_dir = ft_get_some_dir(cmd, "PWD");
	if (pwd_dir != NULL)
	{
		ft_putstr(pwd_dir);
		write(1, "\n", 1);
		free(pwd_dir);
		g_error = 0;
	}
	else if (pwd_dir == NULL)
	{
		new_dir = ft_getcwd(cmd);
		ft_putstr(new_dir);
		write(1, "\n", 1);
		free(new_dir);
		g_error = 0;
	}
}
