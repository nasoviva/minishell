/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utilite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:26:13 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 15:53:02 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_len(char *str)
{
	int		len;
	int		i;

	len = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '|' || str[i] == '>' || str[i] == '<' \
		|| (str[i] == '$' && str[i + 1] && str[i + 1] != '$'))
		{
			i++;
			len++;
		}
		else
			i++;
	}
	return (len * 2);
}

void	ft_if_layer_2(t_cmd *cmd)
{
	ft_free(cmd);
	if (cmd->env_list != NULL)
		ft_free_list(cmd->env_list);
	if (cmd->export_list != NULL)
		ft_free_list(cmd->export_list);
	if (close(cmd->std_in) < 0)
		ft_mistake("Can't close\n", cmd);
	if (close(cmd->std_out) < 0)
		ft_mistake("Can't close\n", cmd);
	clear_history();
}

void	ft_no_input(t_cmd *cmd, char *input)
{
	char	*value;
	int		layer;

	if (input == NULL)
	{
		write(1, "\033[Aminishell$ exit\n", ft_strlen("\033[Aminishell$ exit\n"));
		rl_redisplay();
		value = ft_get_some_dir(cmd, "SHLVL");
		layer = ft_atoi(value);
		free(value);
		if (layer == 2)
		{
			ft_if_layer_2(cmd);
			exit(0);
		}
		else if (layer > 2)
		{
			layer--;
			value = ft_itoa(layer, cmd);
			ft_new_value(cmd->env_list, "SHLVL", value, cmd);
			ft_new_value(cmd->export_list, "SHLVL", value, cmd);
			free(value);
		}
	}
}

void	ft_cmd_create(t_cmd *cmd, char *str)
{
	int	j;

	j = 0;
	if (str)
	{
		cmd->argc = ft_len(str);
		cmd->argv = (char **)malloc(sizeof(char *) * (cmd->argc + 1));
		if (!cmd->argv)
			ft_mistake("Error: Out of memory\n", cmd);
		while (str[cmd->len] && (str[cmd->len] == ' ' || \
		str[cmd->len] == '\t' || str[cmd->len] == '\n'))
			cmd->len++;
		ft_pars(str, cmd, &j);
		ft_final_pars(cmd);
		ft_free_cmd(cmd->argv);
		ft_free_char(str);
	}
}
