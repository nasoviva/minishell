/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:25:32 by hverda            #+#    #+#             */
/*   Updated: 2021/12/15 15:25:34 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_prepars_dollar2(char *str, t_cmd *cmd, int *j)
{
	char	*tmp;

	cmd->out = 0;
	tmp = NULL;
	if (*j < cmd->len)
		tmp = ft_substr(str, *j, cmd->len - *j, cmd);
	cmd->len++;
	*j = cmd->len;
	return (tmp);
}

char	*ft_after(char *str, t_cmd *cmd)
{
	char	*tmp4;

	tmp4 = NULL;
	while (str[cmd->len])
	{
		if (str[cmd->len] == ' ' || str[cmd->len] == '>' || \
		str[cmd->len] == '<' || str[cmd->len] == '|')
			break ;
		else if (str[cmd->len] == '\"' || (str[cmd->len + 1] && str[cmd->len] \
		== '$' && ft_ifkey(str[cmd->len + 1]) == 1) || str[cmd->len] == '\'')
		{
			tmp4 = ft_substr(str, cmd->len, ft_strlen(str) - cmd->len, cmd);
			break ;
		}		
		cmd->len++;
	}
	return (tmp4);
}

char	*ft_check_value(char *tmp2, t_cmd *cmd, int *j)
{
	t_list	*copy;
	char	*tmp3;

	tmp3 = NULL;
	copy = cmd->env_list;
	while (copy && cmd->out == 0)
	{
		if (tmp2 && ft_str_cmp(copy->key, tmp2) == 0)
		{
			if (ft_str_cmp(copy->key, "OLDPWD") == 0 && cmd->oldpwd == 0)
				return (tmp3);
			tmp3 = ft_strdup(copy->value, cmd);
			*j = cmd->len;
			cmd->out = 1;
		}
		copy = copy->next;
	}
	return (tmp3);
}

static char	*ft_result(char *tmp, char *tmp2, char *tmp4, t_cmd *cmd)
{
	char	*tmp5;

	tmp5 = NULL;
	if (cmd->out == 2)
		tmp5 = ft_dollar_2_result2(tmp, tmp2, tmp4, cmd);
	else
		tmp5 = ft_dollar_2_result3(tmp, tmp4, cmd);
	return (tmp5);
}

char	*ft_dollar2(char *str, t_cmd *cmd, int *j)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	char	*tmp5;

	tmp5 = NULL;
	tmp = ft_prepars_dollar2(str, cmd, j);
	tmp4 = ft_after(str, cmd);
	tmp2 = ft_substr(str, *j, cmd->len - *j, cmd);
	ft_if_dollar_null(tmp2, cmd);
	tmp2 = ft_if_dollar_question(tmp2, cmd);
	tmp3 = ft_check_value(tmp2, cmd, j);
	if (tmp4)
	{
		if (cmd->out == 1)
			tmp5 = ft_dollar_2_result1(tmp, tmp3, tmp4, cmd);
		else
			tmp5 = ft_result(tmp, tmp2, tmp4, cmd);
		*j = 0;
		return (tmp5);
	}
	if (!tmp4)
		ft_dollar_2_result(tmp, tmp2, tmp3, cmd);
	return (str);
}
