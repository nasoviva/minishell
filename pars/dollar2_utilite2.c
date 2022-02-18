/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2_utilite2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:03:34 by hverda            #+#    #+#             */
/*   Updated: 2021/12/24 11:03:43 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ifkey(char c)
{
	if (c == '_' || c == '?' || (c >= '0' && c <= '9') || !ft_isalpha(c))
		return (1);
	return (0);
}

void	ft_if_dollar_null(char *tmp2, t_cmd *cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (tmp2 && tmp2[i])
	{
		if (tmp2[i] != '$')
			flag = 1;
		i++;
	}
	if (flag == 0)
	{
		if (tmp2)
		{
			cmd->argv[cmd->k] = ft_strjoin(tmp2, "$", cmd);
		}
		else
			cmd->argv[cmd->k] = ft_strdup("$", cmd);
		cmd->k++;
	}
}
