/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:25:20 by hverda            #+#    #+#             */
/*   Updated: 2021/12/15 15:25:22 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_copykey(char *tmp2, t_cmd *cmd, t_list	*copy)
{
	int	len;

	len = 0;
	if (ft_str_cmp(copy->key, tmp2) == 0)
	{
		if (ft_str_cmp(copy->key, "OLDPWD") == 0 && cmd->oldpwd == 0)
			return (tmp2);
		ft_free_char(tmp2);
		tmp2 = ft_strdup(copy->value, cmd);
		len = ft_strlen(copy->value) + ft_strlen(copy->key);
		if (ft_strlen(copy->value) < ft_strlen(copy->key))
			cmd->len = cmd->len - len;
		cmd->out = 1;
	}
	return (tmp2);
}

char	*ft_if_dollar_question(char *tmp2, t_cmd *cmd)
{
	char	*tmp4;
	char	*tmp3;
	char	*tmp5;

	tmp3 = NULL;
	tmp4 = NULL;
	tmp5 = NULL;
	if (tmp2 && tmp2[0] == '?')
	{
		cmd->out = 2;
		tmp4 = ft_itoa(g_error, cmd);
		tmp5 = ft_substr(tmp2, 1, ft_strlen(tmp2), cmd);
		tmp3 = ft_strjoin(tmp4, tmp5, cmd);
		ft_free_char(tmp2);
		ft_free_char(tmp4);
		ft_free_char(tmp5);
		return (tmp3);
	}
	else
		return (tmp2);
}

char	*ft_if_dollar_question2(char *tmp2, t_cmd *cmd)
{
	char	*tmp4;
	char	*tmp3;
	char	*tmp5;
	int		len;

	len = 0;
	tmp3 = NULL;
	tmp4 = NULL;
	tmp5 = NULL;
	if (tmp2 && tmp2[0] == '?')
	{
		cmd->out = 2;
		tmp4 = ft_itoa(g_error, cmd);
		tmp5 = ft_substr(tmp2, 1, ft_strlen(tmp2), cmd);
		len = ft_strlen(tmp4) + ft_strlen(tmp2);
		if (ft_strlen(tmp4) <= ft_strlen(tmp2))
			cmd->len = cmd->len - len;
		tmp3 = ft_strjoin(tmp4, tmp5, cmd);
		ft_free_char(tmp2);
		ft_free_char(tmp4);
		ft_free_char(tmp5);
		return (tmp3);
	}
	else
		return (tmp2);
}

char	*ft_prepare(char *str, t_cmd *cmd)
{
	char	*tmp;

	tmp = NULL;
	cmd->out = 0;
	tmp = ft_substr(str, 0, cmd->len, cmd);
	cmd->len++;
	str = ft_check_for_dollar(str, cmd);
	return (tmp);
}

char	*ft_dollar(char *str, t_list *env_list, t_cmd *cmd)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	t_list	*copy;
	int		j;

	copy = env_list;
	j = cmd->len;
	tmp3 = NULL;
	tmp2 = NULL;
	tmp = ft_prepare(str, cmd);
	tmp2 = ft_substr(str, j + 1, cmd->len - j - 1, cmd);
	if (*tmp2 == '\0')
		return (ft_onlydollar(str, tmp, tmp2, cmd));
	else
		tmp3 = ft_substr(str, ft_strlen(tmp) + ft_strlen(tmp2) + 1, \
		ft_strlen(str) - ft_strlen(tmp) - ft_strlen(tmp2), cmd);
	tmp2 = ft_if_dollar_question2(tmp2, cmd);
	while (copy && cmd->out == 0)
	{
		tmp2 = ft_copykey(tmp2, cmd, copy);
		copy = copy->next;
	}
	return (ft_dollar_result(tmp, tmp2, tmp3, cmd));
}
