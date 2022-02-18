/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utilite2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:26:41 by hverda            #+#    #+#             */
/*   Updated: 2021/12/15 15:26:43 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pass_quote(char *str, char *tmp, t_cmd *cmd, int *j)
{
	char	*tmp2;

	tmp2 = NULL;
	*j = *j - 1;
	tmp2 = ft_substr(str, *j, cmd->len - *j, cmd);
	cmd->argv[cmd->k] = ft_strjoin(tmp, tmp2, cmd);
	cmd->k++;
	ft_free_char(tmp);
	ft_free_char(tmp2);
	return (str);
}

char	*ft_put(char *tmp, t_cmd *cmd)
{
	cmd->argv[cmd->k] = strdup(tmp);
	ft_free_char(tmp);
	cmd->k++;
	cmd->ok = 1;
	return (NULL);
}

char	*ft_put_in_command(char *tmp, t_cmd *cmd)
{
	int	i;
	int	quote;
	int	quote2;

	i = 0;
	quote = 0;
	quote2 = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\"')
			quote2++;
		else if (tmp[i] == '\'')
			quote++;
		i++;
	}
	if (((quote == 0 || (quote != 0 && quote % 2 != 0)) && \
	(quote2 == 0 || (quote2 != 0 && quote2 % 2 != 0))))
		return (ft_put(tmp, cmd));
	else
		return (tmp);
}

char	*ft_pars_remaind(char *str, char *tmp, t_cmd *cmd, int *j)
{
	char	*tmp2;

	tmp2 = NULL;
	tmp2 = ft_substr(str, cmd->len, ft_strlen(str) - cmd->len, cmd);
	str = ft_strjoin(tmp, tmp2, cmd);
	ft_free_char(tmp);
	ft_free_char(tmp2);
	cmd->len = 0;
	*j = cmd->len;
	while (str[cmd->len] != '\0' && cmd->ok != 1)
	{
		if (cmd->ok != 1 && str[cmd->len] == '\"')
			str = ft_if_quote2(str, cmd, j);
		else if (cmd->ok != 1 && str[cmd->len] == '\'')
			str = ft_if_quote(str, cmd, j);
		else if (cmd->ok != 1 && str[cmd->len] == '$')
			str = ft_dollar2(str, cmd, j);
		else if (cmd->ok != 1)
			cmd->len++;
	}
	cmd->ok = 0;
	return (str);
}

int	ft_check_remaind(char *str, t_cmd *cmd)
{
	int	g;

	g = cmd->len;
	while (str[g] != ' ' && str[g] != '>' && str[g] != '<' && str[g] != '|' && \
	str[g] != '\0')
	{
		g++;
		if (str[g] == '\"')
		{
			g++;
			while (str[g] != '\"' && str[g] != '\0')
				g++;
		}
		else if (str[g] == '\'')
		{
			g++;
			while (str[g] != '\'' && str[g] != '\0')
				g++;
		}
	}
	return (g);
}
