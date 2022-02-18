/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list_exe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:06:59 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:07:01 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_str(t_exe *tmp)
{
	if (tmp->cmdi_path)
		free(tmp->cmdi_path);
	if (tmp->infile)
		free(tmp->infile);
	if (tmp->outfile)
		free(tmp->outfile);
	if (tmp->append)
		free(tmp->append);
	if (tmp->limiter)
		free(tmp->limiter);
}

void	ft_free_list_exe(t_exe *exe)
{
	t_exe	*tmp;
	t_exe	*dell;

	tmp = exe;
	while (tmp)
	{
		dell = tmp;
		ft_free_cmd(tmp->cmd_arg);
		ft_free_str(tmp);
		tmp = tmp->next;
		free(dell);
	}
	exe = NULL;
}
