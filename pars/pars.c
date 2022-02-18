/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:26:06 by hverda            #+#    #+#             */
/*   Updated: 2021/12/15 15:26:08 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_prepars(char *str, t_cmd *cmd, int *j)
{
	*j = cmd->len;
	while (str[cmd->len] != ' ' && str[cmd->len] != '\"' && \
	str[cmd->len] != '\'' && str[cmd->len] != '$' && str[cmd->len] != '>' && \
	str[cmd->len] != '<' && str[cmd->len] != '|' && str[cmd->len] != '\0' \
	&& str[cmd->len] != '\n')
		cmd->len++;
	if (str[cmd->len] == '\"')
		str = ft_if_quote2(str, cmd, j);
	else if (str[cmd->len] == '\'')
		str = ft_if_quote(str, cmd, j);
	else if (str[cmd->len] == '$')
		str = ft_dollar2(str, cmd, j);
	else if (*j < cmd->len)
	{
		cmd->argv[cmd->k] = ft_substr(str, *j, cmd->len - *j, cmd);
		cmd->k++;
	}
	return (str);
}

void	ft_pars(char *str, t_cmd *cmd, int *j)
{
	while (str[cmd->len])
	{
		str = ft_prepars(str, cmd, j);
		while (str[cmd->len] && (str[cmd->len] == ' ' || \
		str[cmd->len] == '>' || str[cmd->len] == '<' || \
		str[cmd->len] == '|' || str[cmd->len] == '\n'))
		{
			if (str[cmd->len] == '>')
				str = ft_outfile(str, cmd, j);
			else if (str[cmd->len] == '<')
				str = ft_infile(str, cmd, j);
			else if (str[cmd->len] == '|')
				str = ft_pipe(str, cmd, j);
			else if (str[cmd->len] == '\0')
				break ;
			else
				cmd->len++;
		}
	}
	cmd->argv[cmd->k] = NULL;
}

static void	ft_command(char *tmp, t_cmd *cmd)
{
	if (cmd->exe->comnd == NULL)
		cmd->exe->comnd = ft_strdup(cmd->argv[cmd->i], cmd);
	else if (cmd->exe->comnd)
	{
		tmp = ft_strjoin(cmd->exe->comnd, "@", cmd);
		free(cmd->exe->comnd);
		cmd->exe->comnd = NULL;
		cmd->exe->comnd = ft_strjoin(tmp, \
		cmd->argv[cmd->i], cmd);
		free(tmp);
	}
}

void	ft_check_pars(t_cmd *cmd)
{
	char	*tmp;

	tmp = NULL;
	while (cmd->argv[cmd->i] != NULL && ft_str_cmp(cmd->argv[cmd->i], "|") != 0)
	{
		if (ft_str_cmp(cmd->argv[cmd->i], "<") == 0)
			ft_if_infile(cmd);
		else if (ft_str_cmp(cmd->argv[cmd->i], ">") == 0)
			ft_if_outfile(cmd);
		else if (ft_str_cmp(cmd->argv[cmd->i], "<<") == 0)
			ft_here_doc(cmd);
		else if (ft_str_cmp(cmd->argv[cmd->i], ">>") == 0)
			ft_if_append(cmd);
		else
			ft_command(tmp, cmd);
		cmd->i++;
	}
}

void	ft_final_pars(t_cmd *cmd)
{
	t_exe	*tmp;

	ft_init_node_exe(cmd);
	tmp = cmd->exe;
	while (cmd->i < cmd->k)
	{
		ft_check_pars(cmd);
		if (cmd->argv[cmd->i] && ft_str_cmp(cmd->argv[cmd->i], "|") == 0)
		{
			cmd->i++;
			cmd->pipe++;
			ft_add_node_back_exe(cmd);
			cmd->exe = cmd->exe->next;
		}
	}
	cmd->exe = tmp;
}
