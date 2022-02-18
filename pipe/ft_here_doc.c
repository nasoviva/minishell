/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:11:31 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:11:33 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_main_pr(t_cmd *cmd)
{
	cmd->exe->fd1 = open("file_here_doc.txt", O_RDONLY);
	if (cmd->exe->fd1 < 0)
		ft_mistake("Can't open or create a file\n", cmd);
	if (dup2(cmd->exe->fd1, STDIN_FILENO) == -1)
		ft_mistake("Error in dup2 with fd1\n", cmd);
	if (close(cmd->exe->fd1) < 0)
		ft_mistake("Can't close\n", cmd);
}

static void	ft_child(t_cmd *cmd)
{
	signal(SIGINT, handler3);
	ft_get_next_line("file_here_doc.txt", cmd->exe->limiter, cmd);
	exit(g_error);
}

void	ft_here_doc(t_cmd *cmd)
{
	pid_t	process;

	if (cmd->argv[cmd->i + 1] == NULL)
	{
		ft_error("minishell: ", "syntax error near unexpected token ", \
		"newline'\n", 258);
	}
	else
	{
		cmd->i++;
		cmd->exe->limiter = ft_strdup(cmd->argv[cmd->i], cmd);
		signal(SIGINT, handler4);
		process = fork();
		if (process < 0)
			ft_mistake("Error in fork\n", cmd);
		if (process == 0)
			ft_child(cmd);
		waitpid(process, &g_error, 0);
		g_error = WEXITSTATUS(g_error);
		ft_main_pr(cmd);
		signal(SIGINT, handler);
	}
}
