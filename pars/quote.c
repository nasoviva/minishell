/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:26:23 by hverda            #+#    #+#             */
/*   Updated: 2021/12/15 15:26:25 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_tmp3(char *tmp3, t_cmd *cmd)
{
	char	*tmp5;
	int		i;

	i = 0;
	tmp5 = NULL;
	while (tmp3[i])
	{
		if (tmp3[i] == '$')
		{
			cmd->f = 1;
			cmd->len = i;
			tmp5 = ft_dollar(tmp3, cmd->env_list, cmd);
			ft_free_char(tmp3);
			tmp3 = tmp5;
		}
		i++;
	}
	return (tmp3);
}

char	*ft_if_dollar(char *str, char *tmp, t_cmd *cmd, int g)
{
	char	*tmp3;
	char	*tmp4;

	tmp3 = ft_substr(str, cmd->len + 1, g - cmd->len - 1, cmd);
	tmp3 = ft_tmp3(tmp3, cmd);
	tmp4 = ft_strjoin(tmp, tmp3, cmd);
	ft_free_char(tmp3);
	ft_free_char(tmp);
	if (cmd->f == 0 || cmd->len < g)
		cmd->len = g;
	return (tmp4);
}

char	*ft_if_quote(char *str, t_cmd *cmd, int *j)
{
	char	*tmp;

	tmp = ft_substr(str, *j, cmd->len - *j, cmd);
	cmd->len++;
	*j = cmd->len;
	while (str[cmd->len])
	{
		if (str[cmd->len] == '\'')
		{
			cmd->quote++;
			break ;
		}
		str = ft_return_str_in(str, tmp, cmd, j);
		str = ft_return_str_out(str, tmp, cmd, j);
		str = ft_return_str_pipe(str, tmp, cmd, j);
		if (str[cmd->len] == '\0')
			break ;
		cmd->len++;
	}
	if (cmd->quote == 0)
		str = ft_pass_quote(str, tmp, cmd, j);
	else
		str = ft_delete_quote(str, tmp, cmd, j);
	cmd->quote = 0;
	return (str);
}

char	*ft_delete_quote(char *str, char *tmp, t_cmd *cmd, int *j)
{
	char	*tmp2;
	char	*tmp3;
	int		g;

	tmp2 = NULL;
	tmp3 = NULL;
	tmp2 = ft_substr(str, *j, cmd->len - *j, cmd);
	tmp3 = ft_strjoin(tmp, tmp2, cmd);
	ft_free_char(tmp2);
	ft_free_char(tmp);
	g = ft_check_remaind(str, cmd);
	if (g > cmd->len)
		tmp = ft_if_dollar(str, tmp3, cmd, g);
	if (tmp)
	{		
		tmp = ft_put_in_command(tmp, cmd);
		if (tmp != NULL)
			return (ft_pars_remaind(str, tmp, cmd, j));
		else
		{
			*j = cmd->len;
			return (str);
		}
	}
	return (str);
}

char	*ft_return_str_pipe(char *str, char *tmp, t_cmd *cmd, int *j)
{
	if (str[cmd->len] == '|')
	{
		if (ft_str_cmp(tmp, "") == 0 && str[cmd->len - 1] == '\"' && \
		str[cmd->len + 1] == '\"' && (str[cmd->len + 2] == ' ' || \
		!str[cmd->len + 2]))
		{
			ft_result_str("\"|\"", cmd);
			*j = cmd->len;
			return (str);
		}
		if (ft_str_cmp(tmp, "") == 0 && str[cmd->len - 1] == '\'' && \
		str[cmd->len + 1] == '\'' && (str[cmd->len + 2] == ' ' || \
		!str[cmd->len + 2]))
		{
			ft_result_str("\'|\'", cmd);
			*j = cmd->len;
			return (str);
		}
	}
	return (str);
}
