/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:26:50 by hverda            #+#    #+#             */
/*   Updated: 2021/12/15 15:26:54 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_result(t_cmd *cmd, char *sign, char *sign2)
{
	if (ft_str_cmp(cmd->argv[cmd->k], sign) == 0)
	{
		ft_free_char(cmd->argv[cmd->k]);
		cmd->argv[cmd->k] = ft_strdup(sign, cmd);
	}
	else if (ft_str_cmp(cmd->argv[cmd->k], sign2) == 0)
	{
		ft_free_char(cmd->argv[cmd->k]);
		cmd->argv[cmd->k] = ft_strdup(sign2, cmd);
	}
	cmd->k++;
}

char	*ft_outfile(char *str, t_cmd *cmd, int *j)
{
	*j = cmd->len;
	cmd->len++;
	if (str[cmd->len] && str[cmd->len] == '>')
	{
		cmd->len++;
		if (str[cmd->len] && str[cmd->len] == '>')
		{
			cmd->len++;
			if (str[cmd->len] == '>')
				return (ft_error_pipe_redir(str, cmd, "token '>>'\n"));
			else
				return (ft_error_pipe_redir(str, cmd, "token '>'\n"));
		}
	}
	cmd->argv[cmd->k] = ft_substr(str, *j, cmd->len - *j, cmd);
	ft_result(cmd, ">>", ">");
	return (str);
}

char	*ft_infile(char *str, t_cmd *cmd, int *j)
{
	*j = cmd->len;
	cmd->len++;
	if (str[cmd->len] && str[cmd->len] == '<')
	{
		cmd->len++;
		if (str[cmd->len] && str[cmd->len] == '<')
		{
			cmd->len++;
			if (str[cmd->len] && str[cmd->len] == '<')
				return (ft_error_pipe_redir(str, cmd, "token '<<'\n"));
			else
				return (ft_error_pipe_redir(str, cmd, "token '<'\n"));
		}
	}
	cmd->argv[cmd->k] = ft_substr(str, *j, cmd->len - *j, cmd);
	ft_result(cmd, "<<", "<");
	return (str);
}

char	*ft_error_pipe_redir(char *str, t_cmd *cmd, char *error)
{
	ft_error("minishell: ", "syntax error near unexpected ", error, 258);
	while (str[cmd->len] != '\0')
		cmd->len++;
	return (str);
}

char	*ft_pipe(char *str, t_cmd *cmd, int *j)
{
	*j = cmd->len;
	if (cmd->len - 1 < 0)
		return (ft_error_pipe_redir(str, cmd, "token '|'\n"));
	cmd->len++;
	if (str[cmd->len] && str[cmd->len] == '|')
		return (ft_error_pipe_redir(str, cmd, "token '||'\n"));
	cmd->argv[cmd->k] = ft_substr(str, *j, cmd->len - *j, cmd);
	cmd->k++;
	return (str);
}
