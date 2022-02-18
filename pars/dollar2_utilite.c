/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2_utilite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:25:41 by hverda            #+#    #+#             */
/*   Updated: 2021/12/15 15:25:44 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_tmp(char *tmp, char *tmp4, char *tmp2, t_cmd *cmd)
{
	if (tmp)
	{
		ft_free_char(tmp);
		tmp = ft_strjoin(tmp4, tmp2, cmd);
	}
	else
		tmp = ft_strdup(tmp2, cmd);
	return (tmp);
}

void	ft_dollar_2_result(char *tmp, char *tmp2, char *tmp3, t_cmd *cmd)
{
	char	*tmp4;

	tmp4 = NULL;
	tmp4 = tmp;
	if (cmd->out == 1)
	{
		if (tmp)
		{
			ft_free_char(tmp);
			tmp = ft_strjoin(tmp4, tmp3, cmd);
		}
		else
			tmp = ft_strdup(tmp3, cmd);
		ft_free_char(tmp3);
	}
	else if (cmd->out == 2)
		tmp = ft_tmp(tmp, tmp4, tmp2, cmd);
	if (tmp)
	{
		cmd->argv[cmd->k] = strdup(tmp);
		cmd->k++;
	}
	ft_free_char(tmp);
	ft_free_char(tmp2);
}

char	*ft_dollar_2_result1(char *tmp, char *tmp3, char *tmp4, t_cmd *cmd)
{
	char	*tmp2;
	char	*tmp5;

	tmp2 = NULL;
	tmp5 = NULL;
	if (tmp)
		tmp2 = ft_strjoin(tmp, tmp3, cmd);
	else
		tmp2 = ft_strdup(tmp3, cmd);
	cmd->len = ft_strlen(tmp2);
	ft_free_char(tmp3);
	tmp5 = ft_strjoin(tmp2, tmp4, cmd);
	cmd->len = 0;
	ft_free_char(tmp);
	ft_free_char(tmp2);
	ft_free_char(tmp4);
	return (tmp5);
}

char	*ft_dollar_2_result2(char *tmp, char *tmp2, char *tmp4, t_cmd *cmd)
{
	char	*tmp3;
	char	*tmp5;

	tmp3 = NULL;
	tmp5 = NULL;
	if (tmp)
		tmp3 = ft_strjoin(tmp, tmp2, cmd);
	else
		tmp3 = ft_strdup(tmp2, cmd);
	cmd->len = ft_strlen(tmp3);
	if (tmp4)
		tmp5 = ft_strjoin(tmp3, tmp4, cmd);
	ft_free_char(tmp);
	ft_free_char(tmp2);
	ft_free_char(tmp3);
	cmd->len = 0;
	ft_free_char(tmp4);
	return (tmp5);
}

char	*ft_dollar_2_result3(char *tmp, char *tmp4, t_cmd *cmd)
{
	char	*tmp2;

	tmp2 = NULL;
	if (tmp)
		tmp2 = ft_strjoin(tmp, tmp4, cmd);
	else
		tmp2 = ft_strdup(tmp4, cmd);
	cmd->len = 0;
	ft_free_char(tmp4);
	ft_free_char(tmp);
	return (tmp2);
}
