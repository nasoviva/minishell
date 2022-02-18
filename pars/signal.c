/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:27:03 by hverda            #+#    #+#             */
/*   Updated: 2021/12/15 15:27:06 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_error = 1;
}

void	handler1(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		write(2, "\n", 1);
		g_error = 130;
		exit(g_error);
	}
	else if (sig == SIGQUIT)
	{
		(void)sig;
		write(2, "Quit: 3\n", 8);
		g_error = 131;
		exit (g_error);
	}
}

void	handler11(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		write(2, "\n", 1);
		g_error = 130;
	}
	else if (sig == SIGQUIT)
	{
		(void)sig;
		write(2, "Quit: 3\n", 8);
		g_error = 131;
	}
}

void	handler3(int sig)
{
	(void)sig;
	exit (1);
}

void	handler4(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}
