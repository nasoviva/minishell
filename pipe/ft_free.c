/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:11:15 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:11:17 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(t_cmd *cmd)
{
	unlink("file_here_doc.txt");
	if (cmd->path)
		free(cmd->path);
	if (cmd->mypathes != NULL)
		ft_free_cmd(cmd->mypathes);
	ft_free_list_exe(cmd->exe);
	if (cmd->proc)
		free(cmd->proc);
}

void	ft_free_cmd(char **argv)
{
	int	i;

	i = 0;
	if (argv)
	{
		while (argv[i])
		{
			free(argv[i]);
			argv[i] = NULL;
			i++;
		}
	}
	free(argv);
	argv = NULL;
}

void	ft_free_char(char *argv)
{
	if (argv != NULL)
	{
		free(argv);
		argv = NULL;
	}
}

void	ft_free_node_data(t_cmd *cmd)
{
	if (cmd->exe->cmdi_path)
		free(cmd->exe->cmdi_path);
	if (cmd->exe->infile)
		free(cmd->exe->infile);
	if (cmd->exe->outfile)
		free(cmd->exe->outfile);
	if (cmd->exe->append)
		free(cmd->exe->append);
	if (cmd->exe->limiter)
		free(cmd->exe->limiter);
}
