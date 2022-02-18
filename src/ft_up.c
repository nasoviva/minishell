/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_up.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:10:08 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:10:10 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_up(t_cmd *cmd)
{
	char	*value;
	int		layer;

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
