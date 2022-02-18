/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utilite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:26:32 by hverda            #+#    #+#             */
/*   Updated: 2021/12/15 15:26:34 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_result_str(char *err, t_cmd *cmd)
{
	cmd->argv[cmd->k] = strdup(err);
	cmd->k++;
	cmd->len++;
	cmd->len++;
}

char	*ft_return_str_in2(char *str, char *tmp, t_cmd *cmd, int *j)
{
	if (str[cmd->len] == '>')
	{
		if (ft_str_cmp(tmp, "") == 0 && str[cmd->len - 1] == '\"' && \
		str[cmd->len + 1] == '>' && str[cmd->len + 2] == '\"' && \
		(str[cmd->len + 3] == ' ' || !str[cmd->len + 3]))
		{
			ft_result_str("\">>\"", cmd);
			cmd->len++;
			*j = cmd->len;
			return (str);
		}
		else if (ft_str_cmp(tmp, "") == 0 && str[cmd->len - 1] == '\"' && \
		str[cmd->len + 1] == '\"' && (str[cmd->len + 2] == ' ' || \
		!str[cmd->len + 2]))
		{
			ft_result_str("\">\"", cmd);
			*j = cmd->len;
			return (str);
		}
	}
	return (str);
}

char	*ft_return_str_out2(char *str, char *tmp, t_cmd *cmd, int *j)
{
	if (str[cmd->len] == '<')
	{
		if (ft_str_cmp(tmp, "") == 0 && str[cmd->len - 1] == '\"' && \
		str[cmd->len + 1] == '<' && str[cmd->len + 2] == '\"' && \
		(str[cmd->len + 3] == ' ' || !str[cmd->len + 3]))
		{
			ft_result_str("\"<<\"", cmd);
			cmd->len++;
			*j = cmd->len;
			return (str);
		}
		else if (ft_str_cmp(tmp, "") == 0 && str[cmd->len - 1] == '\"' && \
		str[cmd->len + 1] == '\"' && (str[cmd->len + 2] == ' ' || \
		!str[cmd->len + 2]))
		{
			ft_result_str("\"<\"", cmd);
			*j = cmd->len;
			return (str);
		}
	}
	return (str);
}

char	*ft_return_str_in(char *str, char *tmp, t_cmd *cmd, int *j)
{
	if (str[cmd->len] == '>')
	{
		if (ft_str_cmp(tmp, "") == 0 && str[cmd->len - 1] == '\'' && \
		str[cmd->len + 1] == '>' && str[cmd->len + 2] == '\'' && \
		(str[cmd->len + 3] == ' ' || !str[cmd->len + 3]))
		{
			ft_result_str("\'>>\'", cmd);
			cmd->len++;
			*j = cmd->len;
			return (str);
		}
		else if (ft_str_cmp(tmp, "") == 0 && str[cmd->len - 1] == '\'' && \
		str[cmd->len + 1] == '\'' && (str[cmd->len + 2] == ' ' || \
		!str[cmd->len + 2]))
		{
			ft_result_str("\'>\'", cmd);
			*j = cmd->len;
			return (str);
		}
	}
	return (str);
}

char	*ft_return_str_out(char *str, char *tmp, t_cmd *cmd, int *j)
{
	if (str[cmd->len] == '<')
	{
		if (ft_str_cmp(tmp, "") == 0 && str[cmd->len - 1] == '\'' && \
		str[cmd->len + 1] == '<' && str[cmd->len + 2] == '\'' && \
		(str[cmd->len + 3] == ' ' || !str[cmd->len + 3]))
		{
			ft_result_str("\'<<\'", cmd);
			cmd->len++;
			*j = cmd->len;
			return (str);
		}
		else if (ft_str_cmp(tmp, "") == 0 && str[cmd->len - 1] == '\'' && \
		str[cmd->len + 1] == '\'' && (str[cmd->len + 2] == ' ' || \
		!str[cmd->len + 2]))
		{
			ft_result_str("\'<\'", cmd);
			*j = cmd->len;
			return (str);
		}
	}
	return (str);
}
