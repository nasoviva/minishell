/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:24:09 by hverda            #+#    #+#             */
/*   Updated: 2021/12/15 15:24:16 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_if_infile(t_cmd *cmd)
{
	if (cmd->argv[cmd->i + 1] == NULL)
		ft_error("minishell: ", "syntax error near unexpected token `newline'", \
		"\n", 1);
	else
	{
		cmd->i++;
		if (cmd->exe->infile)
		{
			free(cmd->exe->infile);
			cmd->exe->infile = NULL;
		}
		cmd->exe->infile = ft_strdup(cmd->argv[cmd->i], cmd);
		cmd->exe->fd1 = open(cmd->exe->infile, O_RDONLY);
		if (cmd->exe->fd1 < 0)
			ft_error("minishell: ", cmd->exe->infile, \
			": No such file or directory\n", 1);
		else
		{
			if (dup2(cmd->exe->fd1, STDIN_FILENO) == -1)
				ft_mistake("Error in dup2 with fd1\n", cmd);
			if (close(cmd->exe->fd1) < 0)
				ft_mistake("Can't close\n", cmd);
		}
	}
}

void	ft_if_outfile(t_cmd *cmd)
{
	if (cmd->argv[cmd->i + 1] == NULL)
		ft_error("minishell: ", "syntax error near unexpected token `newline'", \
		"\n", 1);
	else
	{
		cmd->i++;
		if (cmd->exe->outfile)
		{
			free(cmd->exe->outfile);
			cmd->exe->outfile = NULL;
		}
		cmd->exe->outfile = ft_strdup(cmd->argv[cmd->i], cmd);
		cmd->exe->fd2 = open(cmd->exe->outfile, O_CREAT | O_RDWR | O_TRUNC, \
		0644);
		if (cmd->exe->fd2 < 0)
			ft_error("minishell: ", cmd->exe->outfile, ": Permission denied\n", \
			1);
		else
		{
			if (dup2(cmd->exe->fd2, STDOUT_FILENO) == -1)
				ft_mistake("Error in dup2 with fd2\n", cmd);
			if (close(cmd->exe->fd2) < 0)
				ft_mistake("Can't close\n", cmd);
		}
	}
}

void	ft_if_append(t_cmd *cmd)
{
	if (cmd->argv[cmd->i + 1] == NULL)
		ft_error("minishell: ", "syntax error near unexpected token `newline'", \
		"\n", 1);
	else
	{
		cmd->i++;
		if (cmd->exe->append)
		{
			free(cmd->exe->append);
			cmd->exe->append = NULL;
		}
		cmd->exe->append = ft_strdup(cmd->argv[cmd->i], cmd);
		cmd->exe->fd2 = open(cmd->exe->append, O_CREAT | O_RDWR | O_APPEND, \
		0644);
		if (cmd->exe->fd2 < 0)
			ft_error("minishell: ", cmd->exe->append, ": Permission denied\n", \
			1);
		else
		{
			if (dup2(cmd->exe->fd2, STDOUT_FILENO) == -1)
				ft_mistake("Error in dup2 with fd2\n", cmd);
			if (close(cmd->exe->fd2) < 0)
				ft_mistake("Can't close\n", cmd);
		}
	}
}

void	ft_minishell(t_cmd *cmd, char *input)
{
	add_history(input);
	ft_cmd_create(cmd, input);
	if (cmd->exe->comnd != NULL)
		ft_multiple_pipe(cmd);
	else
	{
		dup2(cmd->std_in, STDIN_FILENO);
		dup2(cmd->std_out, STDOUT_FILENO);
	}
	ft_free(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	char	*input;

	input = NULL;
	if (argc == 1 && argv)
	{
		ft_init(&cmd, envp);
		ft_new_value(cmd.env_list, "SHLVL", "2", &cmd);
		ft_new_value(cmd.export_list, "SHLVL", "2", &cmd);
		while (1)
		{
			signal(SIGINT, handler);
			signal(SIGQUIT, SIG_IGN);
			ft_init_cmd(&cmd);
			input = readline("minishell$ ");
			if (input == NULL)
				ft_no_input(&cmd, input);
			else
				ft_minishell(&cmd, input);
		}
	}
	exit(0);
}
