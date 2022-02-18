/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utilite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:25:54 by hverda            #+#    #+#             */
/*   Updated: 2021/12/15 15:25:56 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_check_for_dollar(char *str, t_cmd *cmd)
{
	while (str[cmd->len])
	{
		if (!ft_ifkey(str[cmd->len]) || str[cmd->len] == ' ')
			break ;
		(cmd->len)++;
	}
	return (str);
}

char	*ft_join(char *tmp, char *tmp3, t_cmd *cmd)
{
	char	*tmp2;

	tmp2 = NULL;
	cmd->len = ft_strlen(tmp);
	if (tmp3)
	{
		if (tmp)
		{
			tmp2 = ft_strjoin(tmp, tmp3, cmd);
			ft_free_char(tmp);
		}
		else
			tmp2 = ft_strdup(tmp3, cmd);
		ft_free_char(tmp3);
	}
	return (tmp2);
}

char	*ft_result_utilite(char *tmp, char *tmp2, t_cmd *cmd)
{
	char	*tmp5;

	tmp5 = NULL;
	tmp5 = ft_strjoin(tmp, tmp2, cmd);
	ft_free_char(tmp);
	ft_free_char(tmp2);
	return (tmp5);
}

char	*ft_dollar_result(char *tmp, char *tmp2, char *tmp3, t_cmd *cmd)
{
	char	*tmp4;
	char	*tmp5;

	tmp4 = NULL;
	tmp5 = NULL;
	if (cmd->out == 1)
	{
		if (tmp)
			tmp4 = ft_result_utilite(tmp, tmp2, cmd);
		else
		{
			tmp4 = ft_strdup(tmp2, cmd);
			ft_free_char(tmp2);
		}
		if (tmp3)
			tmp5 = ft_result_utilite(tmp4, tmp3, cmd);
	}
	else if (cmd->out == 2)
	{
		tmp4 = ft_result_utilite(tmp, tmp2, cmd);
		tmp5 = ft_result_utilite(tmp4, tmp3, cmd);
	}
	else
		tmp5 = ft_join(tmp, tmp3, cmd);
	return (tmp5);
}

char	*ft_onlydollar(char *str, char *tmp, char *tmp2, t_cmd *cmd)
{
	char	*tmp3;
	char	*tmp4;
	char	*tmp5;
	int		j;

	tmp3 = NULL;
	tmp4 = NULL;
	tmp5 = NULL;
	ft_free_char(tmp2);
	tmp2 = ft_strdup("$", cmd);
	cmd->len--;
	j = cmd->len;
	tmp3 = ft_substr(str, ft_strlen(tmp) + ft_strlen(tmp2), j, cmd);
	tmp4 = ft_strjoin(tmp, tmp2, cmd);
	ft_free_char(tmp);
	tmp5 = ft_strjoin(tmp4, tmp3, cmd);
	ft_free_char(tmp2);
	ft_free_char(tmp3);
	ft_free_char(tmp4);
	return (tmp5);
}
