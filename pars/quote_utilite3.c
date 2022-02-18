/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utilite3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:30:39 by hverda            #+#    #+#             */
/*   Updated: 2021/12/24 11:30:41 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_str2(char *str, char *tmp, t_cmd *cmd, int *j)
{
	if (cmd->quote_2 == 0)
		str = ft_pass_quote(str, tmp, cmd, j);
	else
		str = ft_delete_quote(str, tmp, cmd, j);
	cmd->quote_2 = 0;
	return (str);
}

static char	*ft_str(char *str, char *tmp, t_cmd *cmd, int *j)
{
	if (str[cmd->len] == '>')
		str = ft_return_str_in2(str, tmp, cmd, j);
	else if (str[cmd->len] == '<')
		str = ft_return_str_out2(str, tmp, cmd, j);
	else if (str[cmd->len] == '|')
		str = ft_return_str_pipe(str, tmp, cmd, j);
	return (str);
}

char	*ft_if_quote2(char *str, t_cmd *cmd, int *j)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	tmp = ft_substr(str, *j, cmd->len - *j, cmd);
	cmd->len++;
	*j = cmd->len;
	while (str[cmd->len])
	{
		if (str[cmd->len] == '$')
			str = ft_dollar(str, cmd->env_list, cmd);
		else if (str[cmd->len] == '\"')
		{
			cmd->quote_2++;
			break ;
		}
		else
			str = ft_str(str, tmp, cmd, j);
		if (str[cmd->len] == '\0')
			break ;
		else
			cmd->len++;
	}
	str = ft_str2(str, tmp, cmd, j);
	return (str);
}
