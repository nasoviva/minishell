/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_back_exe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:04:45 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:04:48 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_node_back_exe(t_cmd *cmd)
{
	t_exe	*tmp;
	t_exe	*new;

	new = malloc(sizeof (t_exe));
	if (!new)
		ft_mistake("Error: Out of memory\n", cmd);
	if (new)
	{
		new->comnd = NULL;
		new->infile = NULL;
		new->outfile = NULL;
		new->append = NULL;
		new->limiter = NULL;
		new->cmd_arg = NULL;
		new->cmdi_path = NULL;
		cmd->exe->fd1 = STDIN_FILENO;
		cmd->exe->fd2 = STDOUT_FILENO;
		new->next = NULL;
	}
	tmp = cmd->exe;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
