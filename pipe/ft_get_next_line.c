/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:11:23 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:11:24 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_gnl(char **line, int fd, t_cmd *cmd)
{
	int	len;

	len = (int) ft_strlen(*line);
	write(fd, *line, len);
	write(fd, "\n", 1);
	free(*line);
	*line = malloc(sizeof(char) * 1);
	if (!*line)
	{
		close(fd);
		ft_mistake("Error: Out of memory\n", cmd);
	}
	**line = '\0';
}

void	ft_get_next_line(char *file_name, char *limiter, t_cmd *cmd)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	line = readline("> ");
	rl_clear_history();
	if (!line)
	{
		g_error = 0;
		exit(g_error);
	}
	while (ft_str_cmp(line, limiter) != 0)
	{
		ft_gnl(&line, fd, cmd);
		line = readline("> ");
		rl_clear_history();
		if (!line)
		{
			g_error = 1;
			exit(g_error);
		}
	}
}
